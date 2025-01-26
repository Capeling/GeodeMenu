#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    virtual void postUpdate(float dt) {
        m_trailTimer = 69420.42069f;

        LevelEditorLayer::postUpdate(dt);
    }

    QOLMOD_MOD_ALL_HOOKS("smooth-editor-trail")
};
