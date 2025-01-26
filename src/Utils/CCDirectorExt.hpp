#pragma once

#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/CCScheduler.hpp>

using namespace geode::prelude;

class $modify(CCDirectorExt, CCDirector) {
    float getUnmodifiedDelta();
};

class $modify(CCSchedulerExt, CCScheduler) {
    static void onModify(auto& self) {
        if (!self.setHookPriority("cocos2d::CCScheduler::update", -8008135)) {
            geode::log::warn("Failed to set hook priority.");
        }
    }

    virtual void update(float dt);
};
