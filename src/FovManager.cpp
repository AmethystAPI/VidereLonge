#include "FovManager.h"

FovManager::FovManager() {
    initialFov = getFov();
}

uintptr_t FovManager::getAddress() {
    if(hProcess == nullptr) {
        DWORD procId = GetProcessIdByName(L"Minecraft.Windows.exe");
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    }

    return FindDMAAddy(hProcess, SlideAddress(0x05728D28), { 0x10, 0x128, 0x0, 0x110, 0xB0, 0x1B0, 0x18 });
}

__bfloat16 FovManager::getFov() {
    static uintptr_t address = getAddress();
    float fov;

    ReadProcessMemory(hProcess, (BYTE*)address, &fov, sizeof(fov), nullptr);
    if(fov == 0) {
        address = getAddress();
        return getFov();
    }

    return fov;
}

void FovManager::setFov(__bfloat16 fov) {
    static uintptr_t address = getAddress();

    float tmpFov = fov;
    WriteProcessMemory(hProcess, (BYTE*)address, &tmpFov, sizeof(tmpFov), nullptr);
}

void FovManager::resetFov() {
    setFov(initialFov);
}

void FovManager::tick() {
    if(zoom) zoomIn();
    else zoomOut();
}

void FovManager::zoomIn() {
    float fov = getFov();
    if(fov <= 30) return setFov(30);

    float rate = (initialFov - 30) / 20;
    setFov(fov - rate);
}

bool zoomingOut;
void FovManager::zoomOut() {
    float fov = getFov();
    if(fov >= initialFov) { zoomingOut = false; return; };

    zoomingOut = true;
    float rate = (initialFov - 30) / 20;
    setFov(fov + rate);
}

void FovManager::buttonDown() {
    initialFov = zoomingOut ? initialFov : getFov();
    zoom = true;
}

void FovManager::buttonUp() {
    zoom = false;
}