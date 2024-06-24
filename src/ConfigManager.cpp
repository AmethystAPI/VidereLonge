#include "ConfigManager.hpp"

// If anyone knows a better way to do this and make it look cleaner please help me.
ConfigManager::ConfigManager() {
    std::filesystem::path configPath = GetAmethystFolder() / L"mods" / L"VidereLonge@" += MOD_VERSION;
    configPath += "/config.json";
    
    if(!fs::exists(configPath)) {
        Log::Warning("[VidereLonge] config.json does not exist, creating default config");

        std::ofstream out(configPath);

        if(out.is_open())
            out << defaultConfig;

        out.close();
    }

    std::ifstream configFile(configPath);
    if(!configFile.is_open()) {
        Log::Error("[VidereLonge] Failed to open config.json {}", configPath.string());
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

    json sensitivityDampen = data["sensitivityDampen"];
    json targetFov = data["targetFov"];
    json zoomType = data["zoomType"];
    json duration = data["duration"];

    if (!sensitivityDampen.is_number_float())
        throw std::exception("[VidereLonge] Field \"sensitivityDampen\" should be of type \"float\" in config.json");
    if (!targetFov.is_number_float())
        throw std::exception("[VidereLonge] Field \"targetFov\" should be of type \"float\" in config.json");
    if (!zoomType.is_string())
        throw std::exception("[VidereLonge] Field \"zoomType\" should be of type \"string\" in config.json");
    if (!data["duration"].is_number_float())
        throw std::exception("[VidereLonge] Field \"duration\" should be of type \"float\" in config.json");

    this->sensitivityDampen = sensitivityDampen;
    this->targetFov = targetFov;
    this->zoomType = zoomType;
    this->duration = duration;
    Log::Info("[VidereLonge] Successfully loaded config.json from \"{}\"", configPath.string());
}