#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(GameStatsManager) {
    void incrementStat(const char* p0, int p1) {
        if (strcmp(p0, "2") == 0)
            return;

        GameStatsManager::incrementStat(p0, p1);
    }

    QOLMOD_MOD_ALL_HOOKS("freeze-attempts")
};

class $modify(PlayLayer) {
    void resetLevel() {
        auto atts = m_level->m_attempts;

        PlayLayer::resetLevel();

        m_level->m_attempts = atts;
    }

    QOLMOD_MOD_ALL_HOOKS("freeze-attempts")
};
