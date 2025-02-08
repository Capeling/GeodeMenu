/*#ifdef STATUS_TEXTS

#include "Labels.h"
#include "../Hacks/Noclip/Noclip.hpp"
#include "../Hacks/SafeMode/SafeMode.hpp"

bool StatusNode::init()
{
    if (!CCNode::init())
        return false;

    instance = this;

    this->setID("status-node"_spr);
    this->setZOrder(69);
    this->scheduleUpdate();

    topLeft = CCMenu::create();
    topLeft->ignoreAnchorPointForPosition(false);
    topLeft->setID("top-left");
    this->addChild(topLeft);

    topRight = CCMenu::create();
    topRight->ignoreAnchorPointForPosition(false);
    topRight->setID("top-right");
    this->addChild(topRight);

    bottomLeft = CCMenu::create();
    bottomLeft->ignoreAnchorPointForPosition(false);
    bottomLeft->setID("bottom-left");
    this->addChild(bottomLeft);

    bottomRight = CCMenu::create();
    bottomRight->ignoreAnchorPointForPosition(false);
    bottomRight->setID("bottom-right");
    this->addChild(bottomRight);

    int count = 12;

    for (size_t i = 0; i < count; i++)
    {
        auto lbl = CCLabelBMFont::create("", "bigFont.fnt");
        lbl->setAnchorPoint(ccp(0, 1));
        lbl->setPositionX(3);
        lbl->setTag(i);

        sLabels.push_back(lbl);
    }

    sLabels[0]->setString(".");
    as<CCNode*>(sLabels[0]->getChildren()->objectAtIndex(0))->setScale(2.25f);
    as<CCNode*>(sLabels[0]->getChildren()->objectAtIndex(0))->setAnchorPoint(ccp(0.2f, 0.35f));

    hidden = Mod::get()->getSavedValue<bool>("hide-labels");

    update(-1.0f);
    updateFont();
    updateVis();

    reorderSides();
    reorderPosition();

    return true;
}

void StatusNode::updateVis()
{
    float op = 0.9f, scale = 1.0f;

    auto o = numFromString<float>(StatusOpacity::instance->text);
    if (o.isOk())
        op = o.value();

    auto s = numFromString<float>(StatusScale::instance->text);
    if (s.isOk())
        scale = s.value();

    op = clamp<float>(op, 0.0f, 1.0f);

    int y = 0;

    for (size_t i = 0; i < sLabels.size(); i++)
    {
        sLabels[i]->setScale(0.5f * scale);
        sLabels[i]->setOpacity((int)round(255 * op));

        if (hidden)
            sLabels[i]->setVisible(false);
    }

    for (auto lbl : sLabels)
    {
        // make sure all the labels are the same height
        lbl->setScale((32.5f * lbl->getScale()) / lbl->getContentHeight());
    }
}

void StatusNode::updateFont()
{
    std::string font = as<FontModule*>(Client::GetModule("labels-font"))->getSelectedFont();

    for (auto lbl : sLabels)
    {
        lbl->setFntFile(font.c_str());
    }

    log::info("updating font");
}

void StatusNode::reorderSides()
{
    for (auto label : sLabels)
    {
        label->retain();
    }

    topLeft->removeAllChildrenWithCleanup(false);
    topRight->removeAllChildrenWithCleanup(false);
    bottomLeft->removeAllChildrenWithCleanup(false);
    bottomRight->removeAllChildrenWithCleanup(false);

    int i = 0;

    for (auto label : sLabels)
    {
        int side = as<DropdownModule*>(window->modules[i + 4]->options[0])->index;

        label->setAnchorPoint(ccp((side == 0 || side == 2) ? 0 : 1, (side == 2 || side == 3) ? 0 : 1));
        label->setAlignment((side == 0 || side == 2) ? CCTextAlignment::kCCTextAlignmentLeft :
CCTextAlignment::kCCTextAlignmentRight);

        (side == 0 ? topLeft : (side == 1 ? topRight : (side == 2 ? bottomLeft : bottomRight)))->addChild(label);

        i++;

        label->release();
    }
}

void StatusNode::reorderPosition()
{
    float op = 0.9f, scale = 1.0f;

    auto o = numFromString<float>(StatusOpacity::instance->text);
    if (o.isOk())
        op = o.value();

    auto s = numFromString<float>(StatusScale::instance->text);
    if (s.isOk())
        scale = s.value();

    op = clamp<float>(op, 0.0f, 1.0f);

    int v = 0;

    for (size_t i = 0; i < bottomLeft->getChildrenCount(); i++)
    {
        as<CCNode*>(bottomLeft->getChildren()->objectAtIndex(i))->setPosition(ccp(3, 3 + (32.5f * scale * 0.5f) * v));

        if (as<CCNode*>(bottomLeft->getChildren()->objectAtIndex(i))->isVisible())
            v++;
    }

    v = 0;

    for (size_t i = 0; i < bottomRight->getChildrenCount(); i++)
    {
        as<CCNode*>(bottomRight->getChildren()->objectAtIndex(i))->setPosition(ccp(CCDirector::get()->getWinSize().width
- 3, 3 + (32.5f * scale * 0.5f) * v));

        if (as<CCNode*>(bottomRight->getChildren()->objectAtIndex(i))->isVisible())
            v++;
    }

    v = 0;

    for (size_t i = 0; i < topLeft->getChildrenCount(); i++)
    {
        as<CCNode*>(topLeft->getChildren()->objectAtIndex(i))->setPosition(ccp(3, CCDirector::get()->getWinSize().height
- (3 + (32.5f * scale * 0.5f) * v)));

        if (as<CCNode*>(topLeft->getChildren()->objectAtIndex(i))->isVisible())
            v++;
    }

    v = 0;

    for (size_t i = 0; i < topRight->getChildrenCount(); i++)
    {
        as<CCNode*>(topRight->getChildren()->objectAtIndex(i))->setPosition(ccp(CCDirector::get()->getWinSize().width
- 3, CCDirector::get()->getWinSize().height - (3 + (32.5f * scale * 0.5f) * v)));

        if (as<CCNode*>(topRight->getChildren()->objectAtIndex(i))->isVisible())
            v++;
    }
}

class LabelModuleDelegate : public ModuleChangeDelegate
{
    virtual void onModuleChanged(bool enabled)
    {
        if (auto stn = StatusNode::get())
        {
            stn->reorderSides();
            stn->reorderPosition();
        }
    }
};

void StatusNode::postSetup(Window* wnd)
{
    window = wnd;

    auto del = new LabelModuleDelegate();

    for (auto mod : wnd->modules)
    {
        if (mod->id != "labels-in-editor")
        {
            mod->delegate = del;
            mod->options[0]->delegate = del;
        }
    }
}

void StatusNode::update(float dt)
{
    if (!cheat)
        cheat = Client::GetModule("cheat-indicator");

    if (!fps)
        fps = Client::GetModule("status-fps");

    if (!accuracy)
        accuracy = Client::GetModule("status-accuracy");

    if (!deaths)
        deaths = Client::GetModule("status-deaths");

    if (!noclip)
        noclip = Client::GetModule("noclip");

    if (!replay)
        replay = Client::GetModule("status-replay");

    if (!attempt)
        attempt = Client::GetModule("status-attempt");

    if (!message)
        message = Client::GetModule("status-message");

    if (!session)
        session = Client::GetModule("status-session");

    if (!cpsM)
        cpsM = Client::GetModule("status-cps");

    if (!bestRun)
        bestRun = Client::GetModule("best-run");

    if (!clock)
        clock = Client::GetModule("status-clock");

    if (!percentage)
        percentage = Client::GetModule("status-percentage");

    if (!attPL)
        attPL = static_cast<AttemptBaseGameLayer*>(GJBaseGameLayer::get());

    if (!bestRunPlayLayer)
        bestRunPlayLayer = static_cast<BestPlayLayer*>(PlayLayer::get());

    if (!noclipLayer)
        noclipLayer = static_cast<NoclipBaseGameLayer*>(GJBaseGameLayer::get());

    float v = 100 * noclipLayer->getNoclipAccuracy();

    sLabels[0]->setVisible(cheat->enabled);
    sLabels[1]->setVisible(fps->enabled);
    sLabels[2]->setVisible(noclip->enabled && accuracy->enabled);
    sLabels[3]->setVisible(noclip->enabled && deaths->enabled);
    sLabels[4]->setVisible(attempt->enabled);
    sLabels[5]->setVisible(replay->enabled);
    //sLabels[6]->setVisible(replay->enabled && (GJReplayManager::recording || GJReplayManager::playing));
    //sLabels[7]->setVisible(replay->enabled && (GJReplayManager::recording || GJReplayManager::playing));
    sLabels[6]->setVisible(message->enabled);
    sLabels[7]->setVisible(session->enabled);
    sLabels[8]->setVisible(cpsM->enabled);
    sLabels[9]->setVisible(bestRun->enabled);
    sLabels[10]->setVisible(clock->enabled);
    sLabels[11]->setVisible(percentage->enabled);

    if (PlayLayer::get())
    {
        sLabels[2]->setString((numToString(v, 2) + std::string("%")).c_str());
        sLabels[3]->setString((numToString(as<NoclipPlayLayer*>(PlayLayer::get())->m_fields->d, 0) +
(as<NoclipPlayLayer*>(PlayLayer::get())->m_fields->d == 1 ? std::string(" Death") : std::string(" Deaths"))).c_str());
    }
    else
    {
        sLabels[2]->setString("");
        sLabels[3]->setString("");
    }

    sLabels[4]->setString((std::string("Attempt ") + std::to_string(attPL->m_fields->attemptCount)).c_str());



    sLabels[5]->setString("");
    //sLabels[6]->setString(b.c_str());
    //sLabels[7]->setString(inp.str().c_str());
    auto v2 = as<InputModule*>(message->options[1])->text.c_str();
    sLabels[6]->setString(v2);
    sLabels[7]->setString(formatTime(ColourUtility::totalSessionTime).c_str());

    if (PlayLayer::get() && as<NoclipPlayLayer*>(PlayLayer::get())->m_fields->isDead)
    {
        sLabels[2]->stopAllActions();
        sLabels[2]->setColor(ccc3(255, 0, 0));
        sLabels[2]->runAction(CCTintTo::create(0.5f, 255, 255, 255));

        sLabels[3]->stopAllActions();
        sLabels[3]->setColor(ccc3(255, 0, 0));
        sLabels[3]->runAction(CCTintTo::create(0.5f, 255, 255, 255));

        as<NoclipPlayLayer*>(PlayLayer::get())->m_fields->isDead = false;
    }

    if (dt != -1)
    {
        _timeLeft -= dt / CCScheduler::get()->getTimeScale();
        _accum += 1 / (dt / CCScheduler::get()->getTimeScale());
        _frames++;

        if (_timeLeft <= 0) {
            float fps = _accum / _frames;

            sLabels[1]->setString((std::to_string(as<int>(roundf(fps))) + std::string(" FPS")).c_str());
            //CCLOG("Average FPS: %.2f", fps);

            _timeLeft = _updateInterval;
            _accum = 0;
            _frames = 0;
        }
    }

    if (dt != -1)
    {
        for (size_t i = 0; i < cps.size(); i++)
        {
            cps[i] -= dt / CCScheduler::get()->getTimeScale();
        }

        cps.erase(std::remove_if(cps.begin(), cps.end(), [](float i){ return i < 0; }), cps.end());
    }

    sLabels[8]->setString((cpsM->options[1]->enabled ? fmt::format("{} / {} CPS", cps.size(), totalClicks)
: fmt::format("{} CPS", cps.size(), totalClicks)).c_str());

    if (bestRunPlayLayer)
        sLabels[9]->setString(bestRunPlayLayer->getRunString().c_str());
    else
        sLabels[9]->setString("Best Run: Editor");

    sLabels[10]->setString(formatTime().c_str());

    //if (bestRunPlayLayer && bestRunPlayLayer->m_percentageLabel)
    //    sLabels[11]->setString(bestRunPlayLayer->m_percentageLabel->getString());

    updateVis();
}

void StatusNode::updateCPS(float dt)
{

}

class $modify (PlayerObject)
{
    bool pushButton(PlayerButton p0)
    {
        auto ret = PlayerObject::pushButton(p0);

        if (p0 == PlayerButton::Jump && GJBaseGameLayer::get() && GJBaseGameLayer::get()->m_player1 == this)
        {
            if (auto stn = StatusNode::get())
            {
                stn->cps.push_back(1);
                stn->totalClicks++;

                stn->sLabels[8]->stopAllActions();
                stn->sLabels[8]->setColor(ccc3(0, 255, 0));
            }
        }

        return ret;
    }

    bool releaseButton(PlayerButton p0)
    {
        auto ret = PlayerObject::releaseButton(p0);

        if (p0 == PlayerButton::Jump && GJBaseGameLayer::get())
        {
            if (auto stn = StatusNode::get())
            {
                stn->sLabels[8]->stopAllActions();

                if (Client::GetModuleEnabled("status-cps-instant-fade"))
                    stn->sLabels[8]->setColor(ccc3(255, 255, 255));
                else
                    stn->sLabels[8]->runAction(CCTintTo::create(1, 255, 255, 255));
            }
        }

        return ret;
    }
};

class $modify (PlayLayer)
{
    bool init(GJGameLevel* p0, bool p1, bool p2)
    {
        if (!PlayLayer::init(p0, p1, p2))
            return false;

        if (getChildByID("status-node"_spr))
            return true;

        auto stn = StatusNode::create();
        stn->attPL = base_cast<AttemptBaseGameLayer*>(this);
        stn->bestRunPlayLayer = base_cast<BestPlayLayer*>(this);
        this->addChild(stn);

        return true;
    }
};

class $modify (LevelEditorLayer)
{
    bool init(GJGameLevel* p0, bool p1)
    {
        if (!LevelEditorLayer::init(p0, p1))
            return false;

        if (!Client::GetModuleEnabled("labels-in-editor"))
            return true;

        if (getChildByID("status-node"_spr))
            return true;

        if (m_uiLayer)
        {
            auto stn = StatusNode::create();
            stn->attPL = base_cast<AttemptBaseGameLayer*>(this);
            m_uiLayer->addChild(stn);
        }

        return true;
    }
};

void AttemptBaseGameLayer::resetLevelVariables()
{
    if (LevelEditorLayer::get() ? !LevelEditorLayer::get()->m_editorUI->m_playtestStopBtn->isVisible() : true)
        m_fields->attemptCount++;

    if (StatusNode::get())
    {
        StatusNode::get()->totalClicks = 0;

        StatusNode::get()->sLabels[8]->stopAllActions();
        StatusNode::get()->sLabels[8]->setColor(ccWHITE);
    }

    GJBaseGameLayer::resetLevelVariables();

    SafeMode::get()->resetOnNewAttempt();
}

#endif*/
