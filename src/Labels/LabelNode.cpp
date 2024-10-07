#include "LabelNode.hpp"
#include "LabelLayer.hpp"
#include <chrono>

bool LabelNode::init(LabelModule* mod)
{
    if (!CCLabelBMFont::init())
        return false;

    this->mod = mod;

    this->setFntFile(mod->getFont().c_str());

    return true;
}

std::string LabelNode::getFormatString()
{
    return mod->format;
}

void LabelNode::update(float dt)
{
    auto res = rift::compile(getFormatString());

    script = res.unwrapOr(nullptr);
    
    if (!script)
    {
        return this->setString(fmt::format("Error Compiling Script: {}", res.getMessage()).c_str());
    }
    
    script->setVariable("attempt", rift::Value::integer(LabelLayer::get()->getAttempts()));
    script->setVariable("fps", rift::Value::floating(LabelLayer::get()->getFPS()));
    script->setVariable("cps", rift::Value::integer(LabelLayer::get()->getCPS()));

    std::chrono::milliseconds duration(static_cast<long long>(ColourUtility::totalSessionTime * 1000));

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);

    script->setVariable("session_seconds", rift::Value::integer(seconds.count()));
    script->setVariable("session_minutes", rift::Value::integer(minutes.count()));
    script->setVariable("session_hours", rift::Value::integer(hours.count()));

    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    script->setVariable("clock_seconds", rift::Value::integer(localTime->tm_sec));
    script->setVariable("clock_minutes", rift::Value::integer(localTime->tm_min));
    script->setVariable("clock_hours", rift::Value::integer(localTime->tm_hour));

    script->setVariable("isEditor", rift::Value::boolean(LevelEditorLayer::get()));
    script->setVariable("isLevel", rift::Value::boolean(PlayLayer::get()));

    if (PlayLayer::get())
    {
        script->setVariable("bestRun_from", rift::Value::floating(as<BestPlayLayer*>(PlayLayer::get())->m_fields->bestFrom));
        script->setVariable("bestRun_to", rift::Value::floating(as<BestPlayLayer*>(PlayLayer::get())->m_fields->bestTo));
    }

    auto res2 = script->run();

    this->setString(res2.c_str());

    this->setOpacity(mod->getOpacity() * 255);
    this->setScale(mod->getScale() * 0.5f * (32.5f / this->getContentHeight()));

    if (getChildrenCount() == 1 && res2 == ".")
    {
        as<CCNode*>(this->getChildren()->objectAtIndex(0))->setScale(2.25f);
        as<CCNode*>(this->getChildren()->objectAtIndex(0))->setAnchorPoint(ccp(0.2f, 0.35f));
    }
}

LabelNode* LabelNode::create(LabelModule* mod)
{
    auto pRet = new LabelNode();

    if (pRet && pRet->init(mod))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}