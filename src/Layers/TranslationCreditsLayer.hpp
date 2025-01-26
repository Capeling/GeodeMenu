#pragma once

#include <Geode/Geode.hpp>
#include "../Hacks/SafeMode/SafeMode.hpp"
#include "../Client/Module.h"

#include "SillyBaseLayer.h"

using namespace geode::prelude;

class TranslationCreditsLayer : public SillyBaseLayer {
public:
    matjson::Value language;
    std::filesystem::path path;
    GJGroundLayer* ground;
    CCSprite* background;
    ButtonSprite* sprUse;
    CCMenuItemSpriteExtra* btnUse;
    int killCount = 0;

    virtual void customSetup();

    void onPlayerProfile(CCObject* sender);
    void onKill(CCObject* sender);
    void onUse(CCObject* sender);
    void onMessage(CCObject* sender);

    void spawnBigParticle();
    void spawnMediumParticle();
    void spawnSmallParticle();

    static TranslationCreditsLayer* create(matjson::Value language, std::filesystem::path path);
    static TranslationCreditsLayer* addToScene(matjson::Value language, std::filesystem::path path);
};