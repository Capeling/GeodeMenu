#pragma once

#include <Geode/Geode.hpp>
#include "../Dropdown.h"
#include "../Module.h"

using namespace geode::prelude;

class FontModule : public Module {
private:
    std::string font;

public:
    FontModule(std::string id);

    virtual void save();
    virtual void load();

    void makeAndroid(CCNode* menu, CCPoint pos);

    std::string getSelectedFont();

    void onChooseFont(CCObject* sender);
};