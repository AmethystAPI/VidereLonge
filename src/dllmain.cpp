#pragma once

#define NOMINMAX

#include "mc/src-client/common/client/renderer/game/LevelRendererPlayer.hpp"
#include "mc/src-client/common/client/options/BaseOptions.hpp"

#include "amethyst/runtime/events/InputEvents.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/Log.hpp"

#include "ConfigManager.hpp"
#include "dllmain.hpp"

std::chrono::system_clock::time_point enabledStart;
ConfigManager *configManager;
boolean enabled;

SafetyHookInline _LevelRendererPlayer_getFov;

float LevelRendererPlayer_getFov(LevelRendererPlayer* self, float originalFOV, bool applyEffects) {
    static std::string zoomType = configManager->getZoomType();
    static float targetFov = configManager->getTargetFov();
    static float duration = configManager->getDuration();

    float currentFov = _LevelRendererPlayer_getFov.thiscall<float>(self, originalFOV, applyEffects);
    if(currentFov == 70.0f && !applyEffects) return currentFov;

    if(zoomType == "gradual") {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - enabledStart;

        float time = std::clamp(deltaTime.count(), 0.0f, duration);
        float rate = (currentFov - targetFov) / duration;

        if(enabled)
            return currentFov - (time * rate);
        else return targetFov + (time * rate);
    } else if(zoomType == "instant" && enabled) return targetFov;
    
    return currentFov;
}

SafetyHookInline _BaseOptions_getSensitivity;
float BaseOptions_getSensitivity(BaseOptions* self, unsigned int inputMode) {
    static float dampen = (100.0f - configManager->getSensitivityDampen()) / 100.0f;

    static std::string zoomType = configManager->getZoomType();
    static float duration = configManager->getDuration();

    float currentSensitivity = _BaseOptions_getSensitivity.thiscall<float>(self, inputMode);
    float targetSensitivity = currentSensitivity * dampen;

    if(zoomType == "gradual") {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - enabledStart;

        float time = std::clamp(deltaTime.count(), 0.0f, duration);
        float rate = (currentSensitivity - targetSensitivity) / duration;

        if(enabled)
            return (time * -rate) + currentSensitivity;
        else return time * rate;
    } else if(zoomType == "instant" && enabled) return targetSensitivity;

    return currentSensitivity;
}

void RegisterInputs(RegisterInputsEvent &event) {
    Amethyst::InputAction& zoomKeybind = event.inputManager.RegisterNewInput("zoom", {'C'}, true, Amethyst::KeybindContext::Gameplay);
    zoomKeybind.addButtonDownHandler([](FocusImpact focus, ClientInstance& client) {
        enabledStart = std::chrono::system_clock::now();
        enabled = true;
        return Amethyst::InputPassthrough::Consume;
    });

    zoomKeybind.addButtonUpHandler([](FocusImpact focus, ClientInstance& client) {
        enabledStart = std::chrono::system_clock::now();
        enabled = false;
        return Amethyst::InputPassthrough::Consume;
    });
}

void BeforeModShutdown(BeforeModShutdownEvent &event) {
    if (configManager != nullptr)
    {
        delete configManager;
        configManager = nullptr;
    }
}

ModFunction void Initialize(AmethystContext &ctx, const Amethyst::Mod &mod) {
    Amethyst::InitializeAmethystMod(ctx, mod);

    std::string versionedName = mod.mInfo->GetVersionedName();
    configManager = new ConfigManager(ctx.mPlatform.get()->GetAmethystFolder(), versionedName);

    auto &events = Amethyst::GetEventBus();
    events.AddListener<BeforeModShutdownEvent>(BeforeModShutdown);
    events.AddListener<RegisterInputsEvent>(RegisterInputs);

    auto& hooks = Amethyst::GetHookManager();
    HOOK(LevelRendererPlayer, getFov);
    HOOK(BaseOptions, getSensitivity);

    Log::Info("[VidereLonge] Mod successfully initialized!");
}
