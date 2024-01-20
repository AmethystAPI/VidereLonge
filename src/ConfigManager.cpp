#include "ConfigManager.h"

ConfigManager::ConfigManager() {
    std::string configPath = "";//GetAmethystFolder() + "/mods/launcher_config.json/VidereLonge@" + MOD_VERSION + "/config.json";
    
    if(!fs::exists(configPath)) {
        Log::Warning("[VidēreLongē] config.json does not exist, creating default config...");

        std::ofstream out(configPath);

        if(out.is_open())
            out << defaultConfig;
    }

    std::ifstream configFile(configPath);
    if(!configFile.is_open()) {
        Log::Error("[VidēreLongē] Failed to open config.json");
        throw std::exception();
    }

    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();

    json data;
    try {
        data = json::parse(buffer.str());
    } catch (std::exception error) {
        Log::Error("[VidēreLongē] Failed to parse config.json");
        throw error;
    }

    json targetFov = data["targetFov"];
    json zoomType = data["zoomType"];
    json zoomRate = data["zoomRate"];

    if (!targetFov.is_number_float())
        throw std::exception("[VidēreLongē] Field \"targetFov\" should be of type \"float\" in config.json");
    if (!zoomType.is_string())
        throw std::exception("[VidēreLongē] Field \"zoomType\" should be of type \"string\" in config.json");
    if (!data["zoomRate"].is_number_float())
        throw std::exception("[VidēreLongē] Field \"zoomRate\" should be of type \"float\" in config.json");


    this->targetFov = targetFov;
    this->zoomType = zoomType;
    this->zoomRate = zoomRate;

    Log::Info("[VidēreLongē] Loaded config.json successfully!");
}

std::string ConfigManager::getZoomType() {
    return zoomType;
}

float ConfigManager::getTargetFov() {
    return targetFov;
}

float ConfigManager::getZoomRate() {
    return zoomRate;
}