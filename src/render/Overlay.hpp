#pragma once
#include <d3d11.h>
#include <imgui/imgui.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Overlay {
public:
    static bool Initialize(IDXGISwapChain* swapChain);
    static void CleanupDevice();
    static void Render();

    static bool IsMenuVisible();
    static void ToggleMenu();

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    static void SetupImGuiStyle();
};