#pragma once

#include "../Layers/ManageKeybindsLayer.hpp"
#include "../UI/CategoryTabSprite.hpp"
#include "../UI/QOLModMenuBG.hpp"
#include "../Utils/defines.hpp"
#include "ClientSetup.h"
#include "idkwhattocallthis.hpp"

#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class AndroidUI : public geode::Popup<>, TextInputDelegate {
public:
    std::vector<CategoryTabSprite*> sprites = {};
    std::vector<CCMenuItemSpriteExtra*> buttons = {};
    std::vector<CCMenu*> pages = {};
    CCNode* panel = nullptr;
    CCLabelBMFont* searchLabel = nullptr;
    CCMenu* searchResultsPanel = nullptr;
    CCMenu* btnMenu = nullptr;
    TextInput* inputField = nullptr;
    CCLabelBMFont* versionInfo;
    ScrollLayer* scroll = nullptr;
    CCNode* versionParent;
    CCNode* checkingSprite;

    EventListener<Mod::CheckUpdatesTask> updateListener;

    static inline bool hasCheckedForUpdates = false;
    static inline bool updateRequired = false;

    QOLModMenuBG* bg;

    static inline int lastTab = 0;
    static inline int selectedTab = 0;

    void goToPage(int p, bool transition = false);

    void onKeybinds(CCObject*);
    void onPressTab(CCObject* sender);
    void onUpdate(CCObject*);

    void updateVersionLabel();
    void updateTabs();
    void updateSearchBox();

    virtual bool setup();
    virtual void textChanged(CCTextInputNode* p0);
    virtual void update(float dt);
    virtual void keyDown(cocos2d::enumKeyCodes key);

    CCAction* getEnterAction(CCNode* panel);
    CCMenu* getSearchPanel();

    static AndroidUI* addToScene();
    static AndroidUI* create();
    static AndroidUI* get();
};
