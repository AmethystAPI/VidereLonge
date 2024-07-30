#pragma once
#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.hpp"
#include "minecraft/src-client/common/client/options/BaseOptions.hpp"

#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/HookManager.hpp"

#include "ConfigManager.hpp"
#include <chrono>

class ZoomManager {
public:
    ZoomManager(AmethystContext&, ConfigManager*);
    static ZoomManager* getInstance();
    void setEnabled(bool);

private:
    static float sensitivityHook(BaseOptions*, unsigned int);
    static float fovHook(LevelRendererPlayer*, float, bool);
    SafetyHookInline mGetSensitivity;
    SafetyHookInline mGetFov;

    std::chrono::system_clock::time_point mEnabledStart;
    ConfigManager* mConfig;
    bool mEnabled;
};