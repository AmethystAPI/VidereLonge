#include "amethyst/Log.h"
#include "Json.hpp"

#include "amethyst/Utility.h"

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
        "   \"targetFov\": 10.0,\n"             \
        "   \"zoomRate\": 1.5\n"                \
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