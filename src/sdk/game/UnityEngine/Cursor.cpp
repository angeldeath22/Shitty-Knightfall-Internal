#include "Cursor.hpp"
#include <cstdint>
#include <Windows.h>

GetCursorLockState_t UnityInput::GetCursorLockState_Original = nullptr;
SetCursorLockState_t UnityInput::SetCursorLockState_Original = nullptr;
static Unity::CursorLockMode previousCursorState = Unity::CursorLockMode::None;

void UnityInput::Initialize() {
    HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll"); //calling GetModuleHandle Raw #undetected :P
    if (!gameAssembly) {
        return;
    }

    uintptr_t baseAddress = (uintptr_t)gameAssembly;

    uintptr_t getLockState = baseAddress + 0xD828D0; //RVA: [0xD828D0] static UnityEngine::CursorLockMode get_lockState()
    uintptr_t setLockState = baseAddress + 0xD82900; //RVA: [0xD82900] static void set_lockState(UnityEngine::CursorLockMode value)

    GetCursorLockState_Original = reinterpret_cast<GetCursorLockState_t>(getLockState);
    SetCursorLockState_Original = reinterpret_cast<SetCursorLockState_t>(setLockState);

    if (GetCursorLockState_Original && SetCursorLockState_Original) {
        previousCursorState = GetCursorLockState();
    }
    else {

    }
}

void UnityInput::SetCursorLockState(Unity::CursorLockMode mode) {
    if (SetCursorLockState_Original) {
        SetCursorLockState_Original(mode);
    }
    else {

    }
}

Unity::CursorLockMode UnityInput::GetCursorLockState() {
    if (GetCursorLockState_Original) {
        return GetCursorLockState_Original();
    }

    return Unity::CursorLockMode::None;
}

void UnityInput::ToggleCursor() {
    auto currentState = GetCursorLockState();
    SetCursorLockState(currentState == Unity::CursorLockMode::Locked ? Unity::CursorLockMode::None : Unity::CursorLockMode::Locked);
}

void UnityInput::OnMenuOpened() {
    previousCursorState = GetCursorLockState();
    SetCursorLockState(Unity::CursorLockMode::None);
}

void UnityInput::OnMenuClosed() {
    SetCursorLockState(previousCursorState);
}