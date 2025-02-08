#pragma once

#include "../../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

class $modify(TrajectoryPlayerObject, PlayerObject) {
    void playSpiderDashEffect(cocos2d::CCPoint from, cocos2d::CCPoint to);

    QOLMOD_MOD_ALL_HOOKS("show-trajectory")
};

class $modify(TrajectoryEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1);

    virtual void playerTookDamage(PlayerObject* p0);
};

class $modify(TrajectoryBGL, GJBaseGameLayer) {
    struct Fields {
        CCPoint point;
        TrajectoryPlayerObject* trajectoryPlayer;
        CCDrawNode* trajectoryDraw;
    };

    void resetSimulation(PlayerObject* player);
    void simulateTrajectory(bool press, PlayerObject* player);

    void updateSimulation();

    void collisionCheckObjects(PlayerObject* p0, gd::vector<GameObject*>* p1, int p2, float p3);
    virtual void update(float dt);

    QOLMOD_MOD_ALL_HOOKS("show-trajectory")
};

class $modify(TrajectoryPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects);

    void resetLevel();

    virtual void destroyPlayer(PlayerObject* p0, GameObject* p1);

    QOLMOD_MOD_HOOK("show-trajectory", "PlayLayer::resetLevel")
};
