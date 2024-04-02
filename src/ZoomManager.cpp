#include "ZoomManager.hpp"

static ZoomManager* mInstance;
ZoomManager::ZoomManager(AmethystContext* context, ConfigManager* config) {
    mConfig = config;

    context->mHookManager.CreateHook<&BaseOptions::getSensitivity>(ZoomManager::mGetSensitivity, ZoomManager::sensitivityHook);
    context->mHookManager.CreateHook<&LevelRendererPlayer::getFov>(ZoomManager::mGetFov, ZoomManager::fovHook);

    mInstance = this;
}

ZoomManager* ZoomManager::getInstance() {
    return mInstance;
}

void ZoomManager::setEnabled(bool value) {
    mEnabledStart = std::chrono::system_clock::now();
    mEnabled = value;
}

float ZoomManager::fovHook(LevelRendererPlayer* self, float a, bool a2) {
    static ZoomManager* instance = ZoomManager::getInstance();

    static std::string zoomType = instance->mConfig->getZoomType();
    static float targetFov = instance->mConfig->getTargetFov();
    static float duration = instance->mConfig->getDuration();

    float currentFov = instance->mGetFov.thiscall<float>(self, a, a2);
    if(currentFov == 70.0f) return currentFov;

    if(zoomType == "gradual") {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - instance->mEnabledStart;

        float time = std::clamp(elapsedTime.count(), 0.0f, duration);
        float rate = (currentFov - targetFov) / duration;

        if(instance->mEnabled)
            return (time * -rate) + currentFov;
        else return  time * rate;
    } else if(zoomType == "instant" && instance->mEnabled) return targetFov;
    
    return currentFov;
}

float ZoomManager::sensitivityHook(BaseOptions* self, unsigned int inputMode) {
    static ZoomManager* instance = ZoomManager::getInstance();

    static float dampen = (100.0f - instance->mConfig->getSensitivityDampen()) / 100.0f;

    static std::string zoomType = instance->mConfig->getZoomType();
    static float duration = instance->mConfig->getDuration();

    float currentSensitivity = instance->mGetSensitivity.thiscall<float>(self, inputMode);
    float targetSensitivity = currentSensitivity * dampen;

    if(zoomType == "gradual") {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - instance->mEnabledStart;

        float time = std::clamp(elapsedTime.count(), 0.0f, duration);
        float rate = (currentSensitivity - targetSensitivity) / duration;

        if(instance->mEnabled)
            return (time * -rate) + currentSensitivity;
        else return time * rate;
    } else if(zoomType == "instant" && instance->mEnabled) return targetSensitivity;

    return currentSensitivity;
}