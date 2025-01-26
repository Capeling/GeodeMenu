#pragma once

#include "../Module.h"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class SmartStartposUIModule : public Module {
public:
    SmartStartposUIModule();

    void save();
    void load();

    virtual CCSize sizeForOptionsPage();

    void makeAndroid(CCNode* menu, CCPoint pos);
};
