#include "ConfigManager.h"

ConfigManager::ConfigManager() {
    std::string configPath = GetAmethystFolder() + "mods/VidereLonge@" + MOD_VERSION + "/config.json";
    
    if(!fs::exists(configPath)) {
        Log::Warning("[VidereLonge] config.json does not exist, creating default config");

        std::ofstream out(configPath);

        if(out.is_open())
            out << defaultConfig;

        out.close();
    }

    std::ifstream configFile(configPath);
    if(!configFile.is_open()) {
        Log::Error("[VidereLonge] Failed to open config.json {}", configPath);
        throw std::exception();
    }

    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();

    json data;
    try {
        data = json::parse(buffer.str());
    } catch (std::exception error) {
        Log::Error("[VidereLonge] Failed to parse config.json");
        throw error;
    }

    json targetFov = data["targetFov"];
    json zoomType = data["zoomType"];
    json zoomRate = data["zoomRate"];

    if (!targetFov.is_number_float())
        throw std::exception("[VidereLonge] Field \"targetFov\" should be of type \"float\" in config.json");
    if (!zoomType.is_string())
        throw std::exception("[VidereLonge] Field \"zoomType\" should be of type \"string\" in config.json");
    if (!data["zoomRate"].is_number_float())
        throw std::exception("[VidereLonge] Field \"zoomRate\" should be of type \"float\" in config.json");


    this->targetFov = targetFov;
    this->zoomType = zoomType;
    this->zoomRate = zoomRate;
    Log::Info("[VidereLonge] Successfully loaded config.json from \"{}\"", configPath);
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