#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/GameToolbox.hpp>

using namespace geode::prelude;

class $modify(GameToolbox) {
    static gd::string intToShortString(int num) {
        return Client::GetModuleEnabled("no-short-nums") ? gd::string(fmt::format("{}", num).c_str()) : GameToolbox::intToShortString(num);
    }
};
