#pragma once

#define NOMINMAX

#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.hpp"
#include "minecraft/src-client/common/client/options/BaseOptions.hpp"

#include "amethyst/runtime/events/GameEvents.hpp"
#include "amethyst/runtime/events/InputEvents.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/Log.hpp"

#include "ConfigManager.hpp"
#include "ZoomManager.hpp"

ConfigManager* configManager;
ZoomManager* zoomManager;

void RegisterInputs(RegisterInputsEvent& event) { event.inputManager.RegisterNewInput("zoom", { 0x43 }); }
void OnStartJoinGame(OnStartJoinGameEvent& event) {
    auto& inputs = *Amethyst::GetContext().mInputManager;

    inputs.AddButtonDownHandler("zoom", [](FocusImpact focus, ClientInstance& client) {
        zoomManager->setEnabled(true);
    }, false);

    inputs.AddButtonUpHandler("zoom", [](FocusImpact focus, ClientInstance& client) {
        zoomManager->setEnabled(false);
    }, false);
}

void BeforeModShutdown(BeforeModShutdownEvent& event) {
    if(zoomManager != nullptr) {
        delete zoomManager;
        zoomManager = nullptr;
    }

    if(configManager != nullptr) {
        delete configManager;
        configManager = nullptr;
    }
}

extern "C" __declspec(dllexport) void Initialize(AmethystContext& ctx) {
    Amethyst::InitializeAmethystMod(ctx);

    Amethyst::GetContext().mFeatures->enableInputSystem = true;

    ctx.mHookManager->RegisterFunction<&LevelRendererPlayer::getFov>("48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05");
    ctx.mHookManager->RegisterFunction<&BaseOptions::getSensitivity>("40 53 48 83 EC ? 80 B9 ? ? ? ? ? 8B DA");

    configManager = new ConfigManager();
    zoomManager = new ZoomManager(ctx, configManager);

    auto& events = Amethyst::GetEventBus();
    events.AddListener<BeforeModShutdownEvent>(BeforeModShutdown);
    events.AddListener<OnStartJoinGameEvent>(OnStartJoinGame);
    events.AddListener<RegisterInputsEvent>(RegisterInputs);

    Log::Info("[VidereLonge] Mod successfully initialized!");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }