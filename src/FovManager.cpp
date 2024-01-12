#include "FovManager.h"

FovManager::FovManager() {
    initialFov = getFov();
}

HANDLE FovManager::getProccess() {
    DWORD procId = GetProcessIdByName(L"Minecraft.Windows.exe");
    return OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
}

uintptr_t FovManager::getAddress() {
    static HANDLE process = getProccess();
    return FindDMAAddy(process, SlideAddress(0x05728D28), { 0x10, 0x128, 0x0, 0x110, 0xB0, 0x1B0, 0x18 });
}

float FovManager::getFov() {
    static uintptr_t address = getAddress();
    static HANDLE process = getProccess();
    float tmpFov;

    ReadProcessMemory(process, (BYTE*)address, &tmpFov, sizeof(tmpFov), nullptr);
    if(tmpFov == 0) {
        address = getAddress();
        return getFov();
    }

    return tmpFov;
}

void FovManager::setFov(float fov) {
    static uintptr_t address = getAddress();
    static HANDLE process = getProccess();

    float tmpFov = fov;
    WriteProcessMemory(process, (BYTE*)address, &tmpFov, sizeof(tmpFov), nullptr);
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
    if(fov <= 30) return;

    float rate = (initialFov - 30) / 20;
    setFov(fov - rate);
}

bool zoomingOut = false;
void FovManager::zoomOut() {
    float fov = getFov();

    if(fov >= initialFov) { 
        zoomingOut = false; 
        return; 
    }

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