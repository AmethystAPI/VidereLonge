#pragma once
#include "amethyst/Utility.hpp"
#include "amethyst/Log.hpp"
#include "Json.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using json = nlohmann::json;

class ConfigManager {
private:
    std::string defaultConfig = 
        "{\n"                                   \
        "   \"zoomType\": \"gradual\",\n"       \
        "   \"sensitivityDampen\": 90.0,\n"     \
        "   \"targetFov\": 10.0,\n"             \
        "   \"duration\": 0.2\n"                \
        "}";

    float sensitivityDampen;
    float targetFov;
    float duration;

    std::string zoomType;

public:
    ConfigManager();

    inline float getSensitivityDampen() { return sensitivityDampen; }
    inline float getTargetFov() { return targetFov; }
    inline float getDuration() { return duration; }

    std::string getZoomType() { return zoomType; }
};