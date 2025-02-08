#include "../../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/SecretLayer2.hpp>

using namespace geode::prelude;

class $modify(SecretLayer2) {
    static void onModify(auto& self) {
        (void) self.setHookPriority("SecretLayer2::onDoor", 99999999);
        auto hook = self.getHook("SecretLayer2::onDoor");
        Loader::get()->queueInMainThread([hook] {
            Client::GetModule("basement-bypass")->addHookRaw(hook);
        });
    }

    void onDoor(cocos2d::CCObject* sender) {
        auto ugv = GameManager::get()->getUGV("4");
        GameManager::get()->setUGV("4", true);

        SecretLayer2::onDoor(sender);

        GameManager::get()->setUGV("4", ugv);
    }
};
