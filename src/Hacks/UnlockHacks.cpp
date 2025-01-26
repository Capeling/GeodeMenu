#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int id) {
        if (Client::GetModuleEnabled("icon-bypass")) {
            if (type == UnlockType::GJItem) {
                if (id == 18 || id == 19 || id == 20)
                    return true;
            }
        }

        if (id == 16 && Client::GetModuleEnabled("music-bypass") && type == UnlockType::GJItem)
            return true;

        if (id == 17 && Client::GetModuleEnabled("practice-bypass") && type == UnlockType::GJItem)
            return true;

        return GameStatsManager::isItemUnlocked(type, id);
    }
};

class $modify(GameManager) {
    bool isIconUnlocked(int id, IconType type) {
        if (Client::GetModuleEnabled("icon-bypass"))
            return true;

        return GameManager::isIconUnlocked(id, type);
    }

    bool isColorUnlocked(int id, UnlockType type) {
        if (Client::GetModuleEnabled("icon-bypass"))
            return true;

        return GameManager::isColorUnlocked(id, type);
    }
};