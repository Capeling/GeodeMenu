#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class TransAlertLayer : public FLAlertLayer {
public:
    bool init(const char* title, const gd::string& desc, const char* btn);

    static TransAlertLayer* create(const char* title, const gd::string& desc, const char* btn);
};
