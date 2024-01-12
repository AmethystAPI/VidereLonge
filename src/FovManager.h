#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "amethyst/Memory.h"
#include "MemoryUtils.h"
#include <thread>
#include <map>

class FovManager {
private:
    bool zoom = false;
    float initialFov;    

    HANDLE getProccess();
    uintptr_t getAddress();

    float getFov();
    void setFov(float fov);

    void zoomIn();
    void zoomOut();
public:
    FovManager();

    void buttonDown();
    void buttonUp();
    void resetFov();
    void tick();
};