#include "../Client/Client.h"
#include "../Utils/OffsetManager.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

Module* randMod = nullptr;

class $modify(GJBaseGameLayer) {
    void resetLevelVariables() {
        GJBaseGameLayer::resetLevelVariables();

        if (!randMod)
            randMod = Client::GetModule("rand-seed");

        if (randMod->enabled) {
            int seed = 69420;

            auto x = numFromString<int>(as<InputModule*>(randMod->options[0])->text);

            if (x.isOk())
                seed = x.unwrapOr(69420);

#ifdef GEODE_IS_WINDOWS
            *(int*) ((char*) geode::base::get() + OffsetManager::get()->offsetForRandomSeed()) = seed;
#else
            GameToolbox::fast_srand(seed);
#endif
        }
    }
};

class $modify(PlayLayer) {
    void resetLevel() {
        PlayLayer::resetLevel();

        if (!randMod)
            randMod = Client::GetModule("rand-seed");

        if (randMod->enabled) {
            int seed = 69420;

            auto x = numFromString<int>(as<InputModule*>(randMod->options[0])->text);

            seed = x.unwrapOr(69420);

#ifdef GEODE_IS_WINDOWS
            *(int*) ((char*) geode::base::get() + OffsetManager::get()->offsetForRandomSeed()) = seed;
#else
            GameToolbox::fast_srand(seed);
#endif
        }
    }
};
