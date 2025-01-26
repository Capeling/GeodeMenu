#pragma once

#include "../../Client/Client.h"
#include "../../Labels/Labels.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class HackModuleDelegate : public ModuleChangeDelegate {
    virtual void onModuleChanged(bool enabled);
};

class SpeedhackDelegate : public ModuleChangeDelegate {
    virtual void onModuleChanged(bool enabled);
};

class SILLY_DLL SafeMode {
private:
    bool hackedLevelLoad;
    bool hackedAttempt;
    bool hackedAttemptReal;
    std::vector<std::string> reasons;
    std::vector<std::string> loadReasons;

    static inline SafeMode* instance = nullptr;

public:
    bool speedhackKick;
    bool safeEndScreen;

    std::vector<std::string> hacks = {
        "instant",
        "no-reverse",
        "no-static",
        "show-hitboxes",
        "coin-tracers",
        "show-trajectory",
        "rand-seed",
        "jump-hack",
        "tps-bypass",
        "auto-coins",
        "auto-clicker",
        "frame-stepper",
        "hitbox-multiplier",
        "legacy-upside-down",
    };

    static SafeMode* get();

    void resetOnLevelLoad();
    void resetOnNewAttempt();

    void setHackedLoad(std::string reason);
    void setHackedAttempt(std::string reason);

    std::vector<std::pair<bool, std::string>> getReasons();

    void updateSpeedhackShouldKick();

    void addDelegateToModules();
    ccColor3B colourForState();

    bool shouldKickFromLevel();
    void updateIndicator();
};

class $modify(SafePlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects);

    void resetLevel();
    void levelComplete();
    void showNewBest(bool p0, int p1, int p2, bool p3, bool p4, bool p5);
};

class $modify(SafeGJGameLevel, GJGameLevel) {
    void savePercentage(int p0, bool p1, int p2, int p3, bool p4);
};

class $modify(SafeEndLevelLayer, EndLevelLayer) {
    virtual void customSetup();
};
