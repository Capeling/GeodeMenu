#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(PlayerObject) {
    void animatePlatformerJump(float p0) {}

    QOLMOD_MOD_ALL_HOOKS("plat-jump-anim")
};
