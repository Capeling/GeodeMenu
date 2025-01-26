#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void updateProgressbar() {
        PlayLayer::updateProgressbar();

        if (m_percentageLabel && m_attemptLabel) {
            m_percentageLabel->setFntFile(m_attemptLabel->getFntFile());
            m_percentageLabel->setScale(32.5f * 0.5f / m_percentageLabel->getContentHeight());
        }
    }

    QOLMOD_MOD_ALL_HOOKS("percentage-level-font")
};
