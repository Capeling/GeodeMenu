#pragma once

#include "../Client/Client.h"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class LaunchArgs {
private:
    static inline LaunchArgs* instance;

public:
    static LaunchArgs* get();

    bool hasLaunchArg(std::string arg);
};
