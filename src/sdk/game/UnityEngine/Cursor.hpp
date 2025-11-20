#pragma once

namespace Unity {
    enum class CursorLockMode {
        None = 0,
        Locked = 1,
        Confined = 2
    };

}

typedef Unity::CursorLockMode(__stdcall* GetCursorLockState_t)();
typedef void(__stdcall* SetCursorLockState_t)(Unity::CursorLockMode);

class UnityInput {
public:
    static void Initialize();
    static void SetCursorLockState(Unity::CursorLockMode mode);
    static Unity::CursorLockMode GetCursorLockState();
    static void ToggleCursor();
    static void OnMenuOpened();
    static void OnMenuClosed();

private:
    static GetCursorLockState_t GetCursorLockState_Original;
    static SetCursorLockState_t SetCursorLockState_Original;
};