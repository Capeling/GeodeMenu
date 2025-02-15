#include "../Client/Client.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>

using namespace geode::prelude;

class $modify(FMODAudioEngine) {
    void playEffect(gd::string p0, float p1, float p2, float p3) {
        FMODAudioEngine::playEffect("sfx/s4451.ogg", p1, p2, p3);
    }

    QOLMOD_MOD_HOOK("fire-in-the-hole", "FMODAudioEngine::playEffect")
};

class $modify(MusicDownloadManager) {
    gd::string pathForSFX(int p0) {
        return "sfx/s4451.ogg";
    }

    QOLMOD_MOD_HOOK("fire-in-the-hole", "MusicDownloadManager::pathForSFX")
};
