#pragma once

#include "../Window.h"

class Credits : public Window {
public:
    Credits() {
        name = "Credits";
        id = "credits-window";
    }

    void onCredit(CCObject* sender);

    void createPanel(CCMenu* menu, CCPoint pos, const char* title, const char* name, CCNode* img, float scale, std::string v);

    void cocosCreate(CCMenu* menu);
};
