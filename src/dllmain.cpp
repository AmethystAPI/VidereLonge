#pragma once

#define NOMINMAX

#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.hpp"
#include "minecraft/src-client/common/client/options/BaseOptions.hpp"

#include "amethyst/runtime/events/EventManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/Log.hpp"

#include "ConfigManager.hpp"
#include "ZoomManager.hpp"

ConfigManager* configManager;
ZoomManager* zoomManager;

AmethystContext* context;

void RegisterInputs(Amethyst::InputManager* input) { input->RegisterNewInput("zoom", { 0x43 }); }
void OnStartJoinGame(ClientInstance* ci) {
    context->mInputManager.AddButtonDownHandler("zoom", [](FocusImpact focus, ClientInstance& client) {
        zoomManager->setEnabled(true);
    }, false);

    context->mInputManager.AddButtonUpHandler("zoom", [](FocusImpact focus, ClientInstance& client) {
        zoomManager->setEnabled(false);
    }, false);
}

void BeforeModShutdown() {
    if(zoomManager != nullptr) {
        delete zoomManager;
        zoomManager = nullptr;
    }

    if(configManager != nullptr) {
        delete configManager;
        configManager = nullptr;
    }
}

extern "C" __declspec(dllexport) void Initialize(AmethystContext* ctx) {
    context = ctx;

    context->mHookManager.RegisterFunction<&LevelRendererPlayer::getFov>("48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05");
    context->mHookManager.RegisterFunction<&BaseOptions::getSensitivity>("40 53 48 83 EC ? 80 B9 ? ? ? ? ? 8B DA");

    configManager = new ConfigManager();
    zoomManager = new ZoomManager(context, configManager);

    context->mEventManager.beforeModShutdown.AddListener(BeforeModShutdown);
    context->mEventManager.onStartJoinGame.AddListener(OnStartJoinGame);
    context->mEventManager.registerInputs.AddListener(RegisterInputs);

    Log::Info("[VidereLonge] Mod successfully initialized!");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }