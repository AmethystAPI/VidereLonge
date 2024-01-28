#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.h"
#include "amethyst/events/EventManager.h"
#include "amethyst/InputManager.h"
#include "amethyst/HookManager.h"
#include "amethyst/Log.h"

#include "ConfigManager.h"

#define ModFunction extern "C" __declspec(dllexport)

ConfigManager configManager;
HookManager hookManager;
float initialFov;
bool releasing;
bool pressed;
float fov;

LevelRendererPlayer::_getFov getFov;
static float LevelRendererPlayer_getFov(LevelRendererPlayer* self, float a, bool applyEffects) {
    if(pressed || releasing) return fov;
    else {
        initialFov = getFov(self, a, applyEffects);
        return fov = initialFov;
    }
}

inline void gradualPress() {
    static float targetFov = configManager.getTargetFov();
    static float zoomRate = configManager.getZoomRate();

    if(fov <= targetFov) fov = targetFov;
    else fov -= zoomRate;
}

inline void gradualRelease() {
    static float zoomRate = configManager.getZoomRate();

    if(fov >= initialFov) {
        releasing = false;
        fov = initialFov;
    } else fov += zoomRate;
}

void OnTick() {
    static std::string type = configManager.getZoomType();
    static float targetFov = configManager.getTargetFov();
    
    if(type == "gradual") {
        if(pressed) gradualPress();
        else if(releasing) gradualRelease();
    } else if(type == "instant") {
        if(pressed) fov = targetFov;
        else if(releasing) fov = initialFov;
    }
}

ModFunction void RegisterInputs(InputManager* inputManager) { inputManager->RegisterInput("zoom", 0x56); }
ModFunction void Initialize(Amethyst::EventManager* eventManager, InputManager* inputManager) {
    MH_Initialize();

    hookManager.CreateHook(
        SigScan("48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05"),
        &LevelRendererPlayer_getFov, reinterpret_cast<void**>(&getFov));

    inputManager->AddButtonDownHandler("zoom", [](FocusImpact f, ClientInstance c) {
        releasing = false;
        pressed = true;
    });

    inputManager->AddButtonUpHandler("zoom", [](FocusImpact f, ClientInstance c) {
        static std::string type = configManager.getZoomType();

        if(type == "gradual") releasing = true;
        pressed = false;
    });

    eventManager->beforeTick.AddListener(OnTick);

    Log::Info("[VidereLonge] Mod successfully initialized!");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }