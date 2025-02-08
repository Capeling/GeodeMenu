#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/EditLevelLayer.hpp>

using namespace geode::prelude;

class $modify(EditLevelLayer) {
    void onShare(CCObject* sender) {
        if (Client::GetModuleEnabled("noc-hack")) {
            this->m_level->m_originalLevel = 0;
        }

        EditLevelLayer::onShare(sender);
    }
};
