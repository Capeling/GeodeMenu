#ifndef GEODE_IS_MACOS

# include "../Client/Client.h"

# include <Geode/Geode.hpp>
# include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    void constrainGameLayerPosition(float p0, float p1) {}

    QOLMOD_MOD_HOOK("free-scroll", "EditorUI::constrainGameLayerPosition")
};

#endif
