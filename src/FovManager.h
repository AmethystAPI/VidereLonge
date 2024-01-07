#include "amethyst/Memory.h"
#include "MemoryUtils.h"
#include <thread>
#include <map>

class FovManager {
private:
    __bfloat16 initialFov;
    HANDLE hProcess;
    bool zoom;

    uintptr_t getAddress();
public:
    FovManager();

    __bfloat16 getFov();
    void setFov(__bfloat16 fov);
    void resetFov();

    void tick();
    void zoomIn();
    void zoomOut();

    void buttonUp();
    void buttonDown();
};