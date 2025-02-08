#pragma once

#include "../Client/Module.h"
#include "SillyBaseLayer.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/TextAlertPopup.hpp>

using namespace geode::prelude;

class IconOptionsLayer : public SillyBaseLayer, public ColorPickPopupDelegate {
public:
    int icon;
    ccColor3B startFade;
    ccColor3B endFade;
    CCScale9Sprite* spr1;
    CCScale9Sprite* spr2;
    TextInput* input;

    void onClose(CCObject* sender);

    void onColour(CCObject* sender);
    virtual void customSetup();

    static IconOptionsLayer* create(int icon) {
        IconOptionsLayer* pRet = new IconOptionsLayer();

        pRet->icon = icon;

        if (pRet && pRet->initWithSizeAndName(ccp(350, 180), "Edit Icon Effects")) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            return nullptr;
        }
    }

    static IconOptionsLayer* addToScene(int icon) {
        auto pRet = IconOptionsLayer::create(icon);

        CCScene::get()->addChild(pRet, 99999);

        return pRet;
    }

    virtual void updateColor(const cocos2d::ccColor4B& color);
};
