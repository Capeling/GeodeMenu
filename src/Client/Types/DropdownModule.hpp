#pragma once

#include "../Dropdown.h"
#include "../Module.h"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class DropdownModule : public Module {
public:
    std::vector<std::string> content = {};
    int index = 0;

    DropdownModule(std::vector<std::string> stuff, std::string id, int def);

    void save();
    void load();

    void makeAndroid(CCNode* menu, CCPoint pos);

    void onDropdownSelectionChanged(CCObject* sender);
};
