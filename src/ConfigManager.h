#include "amethyst/Utility.h"
#include "amethyst/Log.h"
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
        "{"                                     \
        "   \"zoomType\": \"gradual\","         \
        "   \"targetFov\": 10.0,"               \
        "   \"zoomRate\": 1.5"                  \
        "}";

    std::string zoomType;
    float targetFov;
    float zoomRate;

public:
    ConfigManager();

    std::string getZoomType();
    float getTargetFov();
    float getZoomRate();
};