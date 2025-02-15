#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(PlayerObject) {
    virtual void update(float dt) {
        if (m_regularTrail)
            m_regularTrail->setBlendFunc(this->getBlendFunc());

        PlayerObject::update(dt);
    }

    QOLMOD_MOD_ALL_HOOKS("no-trail-blending")
};
