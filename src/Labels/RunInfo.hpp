#pragma once

#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(RunPlayLayer, PlayLayer) {
    struct Fields {
        float fromPercent;
    };

    void resetLevel();
};
