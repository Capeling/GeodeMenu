/*#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "../Client/Client.h"

CCPoint startPos = CCPointZero;
bool ignoreStuff = false;

class $modify (PlayerObjectExt, PlayerObject)
{
    bool isHeld;

    TodoReturn pushButton(PlayerButton p0)
    {
        PlayerObject::pushButton(p0);

        if (p0 == PlayerButton::Jump)
            m_fields->isHeld = true;
    }

    TodoReturn releaseButton(PlayerButton p0)
    {
        PlayerObject::releaseButton(p0);

        if (p0 == PlayerButton::Jump)
            m_fields->isHeld = false;
    }
};

/*class $modify (EffectGameObject)
{
    virtual TodoReturn triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2)
    {
        if (!ignoreStuff)
            EffectGameObject::triggerObject(p0, p1, p2);
    }
};


class $modify (GJBaseGameLayer)
{
    TodoReturn gameEventTriggered(GJGameEvent p0, int p1, int p2)
    {
        if (!ignoreStuff)
            GJBaseGameLayer::gameEventTriggered(p0, p1, p2);
    }

    /*bool canBeActivatedByPlayer(PlayerObject* p0, EffectGameObject* p1)
    {
        if (ignoreStuff)
            return false;

        return GJBaseGameLayer::canBeActivatedByPlayer(p0, p1);
    }

    void destroyObject(GameObject* p0)
    {
        if (!ignoreStuff)
            GJBaseGameLayer::destroyObject(p0);
    }
};

class $modify (PlayLayer)
{
    CCDrawNode* dn;
    PlayerObject* plr;
    CCLayer* mainLayer = nullptr;

    virtual TodoReturn destroyPlayer(PlayerObject* p0, GameObject* p1)
    {
        if ((p0 && p0->getID() == "trajectory-player"_spr) || ignoreStuff)
        {
            p0->m_isDead = true;

            return;
        }

        PlayLayer::destroyPlayer(p0, p1);
    }

    static void onModify(auto& self) {
        self.setHookPriority("PlayLayer::destroyPlayer", 6969);
    }

    void incrementJumps()
    {
        if (!ignoreStuff)
            PlayLayer::incrementJumps();
    }

    TodoReturn playEndAnimationToPos(cocos2d::CCPoint p0)
    {
        if (!ignoreStuff)
            PlayLayer::playEndAnimationToPos(p0);
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects)
    {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        if (!m_fields->mainLayer)
        {
            if (auto mainNode = getChildOfType<CCNode>(this, 1))
            {
                if (auto l = getChildOfType<CCLayer>(mainNode, 0))
                {
                    m_fields->mainLayer = l;
                }
            }
        }

        auto plr = PlayerObject::create(1, 1, this, m_fields->mainLayer, false);
	    plr->setPosition({0, 105});
	    plr->setVisible(false);
        plr->setID("trajectory-player"_spr);
	    m_fields->mainLayer->addChild(plr);
        plr->pushButton(PlayerButton::Jump);

        CCPoint point = plr->getPosition();

        auto dn = CCDrawNode::create();
        dn->setID("trajectory-node"_spr);
        m_fields->mainLayer->addChild(dn);

        m_fields->dn = dn;
        m_fields->plr = plr;

        return true;
    }

    int getGamemode(PlayerObject* plr)
    {
        if (plr->m_isShip)
            return 1;

        if (plr->m_isBall)
            return 2;

        if (plr->m_isBird)
            return 3;

        if (plr->m_isDart)
            return 4;

        if (plr->m_isRobot)
            return 5;

        if (plr->m_isSpider)
            return 6;

        if (plr->m_isSwing)
            return 7;

        return 0;
    }

    void perform(PlayerObject* play, bool first = false)
    {
        auto plr = m_fields->plr;
        auto dn = m_fields->dn;

        int updateRate = 5;
        int steps = 150;

        bool held = as<PlayerObjectExt*>(m_player1)->m_fields->isHeld == first;

        CCPoint point = (first && (getGamemode(m_player1) == 0 || getGamemode(m_player1) == 5)) ? m_player1->m_lastGroundedPos : m_player1->getPosition();
        plr->setPosition(point);
        plr->m_isPlatformer = m_player1->m_isPlatformer;
        plr->m_isUpsideDown = plr->m_isUpsideDown;
        plr->m_isDead = false;
        plr->m_vehicleSize = m_player1->m_vehicleSize;

        plr->m_yVelocity = m_player1->m_yVelocity;
        plr->m_vehicleSize = m_player1->m_vehicleSize;
        plr->m_isShip = m_player1->m_isShip;
        plr->m_isBall = m_player1->m_isBall;
        plr->m_isBird = m_player1->m_isBird;
        plr->m_isDart = m_player1->m_isDart;
        plr->m_isRobot = m_player1->m_isRobot;
        plr->m_isSpider = m_player1->m_isSpider;
        plr->m_isSwing = m_player1->m_isSwing;

        for (size_t i = 0; i < updateRate * steps; i++) {
            plr->update(0.2f);
            plr->updateSpecial(0.2f);
            this->checkCollisions(plr, 1, false);
            
            dn->drawSegment(point, plr->getPosition(), 1, ccc4f(0, held ? 1 : 0.45f, 0, 1));
            point = plr->getPosition();

            if (plr->m_isDead)
            {
                CCPoint squareSize = plr->getObjectRect().size;
                CCPoint squarePosition = plr->getPosition();

                CCPoint squareVertices[] = {
                    ccp(squarePosition.x - squareSize.x / 2, squarePosition.y - squareSize.y / 2), // Bottom-left
                    ccp(squarePosition.x + squareSize.x / 2, squarePosition.y - squareSize.y / 2), // Bottom-right
                    ccp(squarePosition.x + squareSize.x / 2, squarePosition.y + squareSize.y / 2), // Top-right
                    ccp(squarePosition.x - squareSize.x / 2, squarePosition.y + squareSize.y / 2)  // Top-left
                };

                dn->drawPolygon(squareVertices, 4, ccc4f(0, 0, 0, 0), 0.35f, ccc4f(1, 0, 0, 1));

                return;
            }
        }
    }

    virtual TodoReturn postUpdate(float p0)
    {
        PlayLayer::postUpdate(p0);

        ignoreStuff = true;

        auto dn = m_fields->dn;
        auto plr = m_fields->plr;

        dn->clear();

        plr->pushButton(PlayerButton::Jump);
        perform(nullptr, true);

        plr->releaseButton(PlayerButton::Jump);
        perform(nullptr);

        ignoreStuff = false;
    }
};*/