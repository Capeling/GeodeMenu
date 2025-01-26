#pragma once

#include <Geode/Geode.hpp>
#include "LabelCommon.hpp"
#include "../Client/Module.h"

using namespace geode::prelude;

class LabelModule : public Module {
private:
    float scale = 1;
    float opacity = 1;
    std::string font = "bigFont.fnt";
    LabelAnchor side = LabelAnchor::TopLeft;

public:
    CCPoint offset;
    CCLabelBMFont* labelNode = nullptr;
    std::string format;
    int presetType = -1;
    bool isCheatIndicator = false;
    bool noclipOnly = false;
    std::vector<LabelEvent> events;
    bool visible = true;

    LabelModule(std::string format, std::string font);

    void setFont(std::string newFont);
    std::string getFont();

    void setScale(float newScale);
    float getScale();

    void setOpacity(float newOpacity);
    float getOpacity();

    void setSide(LabelAnchor newSide);
    LabelAnchor getSide();

    ccColor3B getColour();

    matjson::Value saveToObject();
    static LabelModule* createFromObject(matjson::Value obj);

    void exportToFile();
};