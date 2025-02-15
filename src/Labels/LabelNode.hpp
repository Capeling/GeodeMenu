#pragma once

#include "../Client/Client.h"
#include "BestRun.hpp"
#include "LabelModule.hpp"
#include "RunInfo.hpp"

#include <Geode/Geode.hpp>
#include <rift.hpp>

using namespace geode::prelude;

class LabelNode : public CCNode {
public:
    LabelModule* mod;
    CCLabelBMFont* label;
    rift::Script* script;

    bool init(LabelModule* mod);

    virtual void update(float dt);

    std::string getFormatString();

    static LabelNode* create(LabelModule* mod);

    ~LabelNode();
};
