#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void addObject(GameObject* obj) {
        obj->m_hasNoGlow = true;

        PlayLayer::addObject(obj);
    }

    QOLMOD_MOD_HOOK("no-glow", "PlayLayer::addObject")
};
