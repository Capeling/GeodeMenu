#pragma once

#include "../Client/Client.h"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CCPastelLabelBMFont : public CCLabelBMFont {
public:
    static CCPastelLabelBMFont* create(const char* text, const char* fontFile);
    void update(float dt);

protected:
    CCPastelLabelBMFont();
    virtual ~CCPastelLabelBMFont();

    bool initWithString(const char* text, const char* fontFile);
};
