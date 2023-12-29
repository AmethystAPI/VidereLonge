#include <Windows.h>

#include "amethyst/HookManager.h"
#include "amethyst/Log.h"
#include "MinHook.h"

#include "minecraft/src-client/common/client/renderer/screen/MinecraftUIRenderContext.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"

static ClientInstance* gameClient = nullptr;
HookManager hookManager;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }

// Called when a mod is loaded by AmethystAPI, used to create hooks
extern "C" __declspec(dllexport) void Initialize(const char* gameVersion) { MH_Initialize(); }

// Called every 50ms, currently not hooked into a real tick function
extern "C" __declspec(dllexport) void OnTick() {}

// ClientInstance::onStartJoinGame
extern "C" __declspec(dllexport) void OnStartJoinGame(ClientInstance* instance) { gameClient = instance; }

// Hooked ScreenView::setupAndRender for mods to draw UI
extern "C" __declspec(dllexport) void OnRenderUI(ScreenView* screenView, MinecraftUIRenderContext* ctx) {}

// Used to destroy hooks for hot-reloading
extern "C" __declspec(dllexport) void Shutdown() { hookManager.Shutdown(); }