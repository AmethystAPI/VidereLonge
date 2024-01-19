#include "amethyst/InputManager.h"
#include "amethyst/HookManager.h"
#include "amethyst/Log.h"
#include "FovManager.h"

#define ModFunction extern "C" __declspec(dllexport)

ClientInstance* gameClient = nullptr;
HookManager hookManager;
FovManager* fovManager;

ModFunction void RegisterInputs(InputManager* inputManager) { inputManager->RegisterInput("zoom", 0x43); }
ModFunction void Initialize(const char* _, InputManager* inputManager) {
    MH_Initialize();

    inputManager->AddButtonDownHandler("zoom", [](FocusImpact f, ClientInstance c) { if(fovManager != nullptr) fovManager->buttonDown(); });
    inputManager->AddButtonUpHandler("zoom", [](FocusImpact f, ClientInstance c) { if(fovManager != nullptr) fovManager->buttonUp(); });
}

ModFunction void OnStartJoinGame(ClientInstance* clientInstance) { 
    gameClient = clientInstance;
}

ModFunction void AfterTick() {
    if(gameClient == nullptr) return;

    LocalPlayer* player = gameClient->getLocalPlayer();
    if(player == nullptr && fovManager != nullptr) {
        fovManager->resetFov();
        delete fovManager;
        fovManager = nullptr;
    } else if(player != nullptr && fovManager == nullptr)
        fovManager = new FovManager();
    else if(player != nullptr && fovManager != nullptr)
        fovManager->tick();
}

ModFunction void Shutdown() {
    if(fovManager != nullptr) {
        fovManager->resetFov();
        free(fovManager);
    }

    hookManager.Shutdown();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }