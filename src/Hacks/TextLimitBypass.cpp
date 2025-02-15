#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/CCTextInputNode.hpp>

using namespace geode::prelude;

class $modify(CCTextInputNode) {
    void updateLabel(gd::string p0) {
        if (this->getID().starts_with("IGNOREBYPASSES"_spr)) {
            CCTextInputNode::updateLabel(p0);

            return;
        }

        if (Client::GetModuleEnabled("char-limit"))
            CCTextInputNode::setMaxLabelLength(6969);

        if (Client::GetModuleEnabled("char-filter"))
            CCTextInputNode::setAllowedChars(
                "!\"#$%&'()*+,-./"
                "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ "
            );

        CCTextInputNode::updateLabel(p0);
    }
};
