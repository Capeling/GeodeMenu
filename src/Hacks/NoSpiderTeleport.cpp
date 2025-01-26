#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

#ifdef QOLMOD_NO_SPIDER_DASH

class $modify(PlayerObject) {
    void playSpiderDashEffect(cocos2d::CCPoint from, cocos2d::CCPoint to) {}

    QOLMOD_MOD_ALL_HOOKS("no-spider-dash")
};

#endif
