#include "minecraft/src-client/common/client/renderer/LevelRendererPlayer.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"

#include "amethyst/InputManager.h"
#include "amethyst/HookManager.h"
#include "amethyst/Log.h"
#include "MinHook.h"

#include "FovManager.h"
#include <thread>

#define ModFunction extern "C" __declspec(dllexport)

static ClientInstance* gameClient = nullptr;
FovManager* fovManager = new FovManager();
HookManager hookManager;

ModFunction void RegisterInputs(InputManager* inputManager) { inputManager->RegisterInput("zoom", 0x43); }

ModFunction void Initialize(const char* gameVersion, InputManager* inputManager) { 
    MH_Initialize();

    inputManager->AddButtonDownHandler("zoom", [](FocusImpact fi, IClientInstance ci) { fovManager->buttonDown(); });
    inputManager->AddButtonUpHandler("zoom", [](FocusImpact fi, IClientInstance ci) { fovManager->buttonUp(); });
}

ModFunction void OnTickAfter() { fovManager->tick(); }
ModFunction void Shutdown() {
    fovManager->resetFov();
    free(fovManager);

    hookManager.Shutdown();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }