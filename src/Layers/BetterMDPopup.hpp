#pragma once

#include "SillyBaseLayer.h"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BetterMDPopup : public FLAlertLayer {
public:
    bool init(
        FLAlertLayerProtocol* delegate, const char* title, gd::string desc, const char* btn1, const char* btn2, float width, bool scroll,
        float height, float textScale
    );

    static BetterMDPopup* create(
        FLAlertLayerProtocol* delegate, const char* title, gd::string desc, const char* btn1, const char* btn2, float width, bool scroll,
        float height, float textScale
    );
    static BetterMDPopup* create(const char* title, gd::string desc, const char* btn1, const char* btn2);
};
