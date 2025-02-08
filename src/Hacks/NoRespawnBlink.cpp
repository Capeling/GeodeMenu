#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(CCNode) {
    CCAction* runAction(CCAction* action) {
        if (PlayLayer::get() && (PlayLayer::get()->m_player1 == as<CCNode*>(this) || PlayLayer::get()->m_player2 == as<CCNode*>(this)) &&
            action->getTag() == 11)
            return action;

        return CCNode::runAction(action);
    }

    static void onModify(auto& self) {
        auto hook = self.getHook("CCNode::runAction");

        Loader::get()->queueInMainThread([hook] {
            auto modu = Client::GetModule("no-blink");
            modu->addHookRaw(hook);
        });
    }
};
