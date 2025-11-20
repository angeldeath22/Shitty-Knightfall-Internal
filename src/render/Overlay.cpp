#include "Overlay.hpp"
#include "interface/Menu.hpp"
#include "../utils/CMD/Logger.hpp"

#include "directx/Device.hpp"
#include "directx/Renderer.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "resources/font.hpp"

#include <typedef.h>
#include "../features/ESP.hpp"
#include "../sdk/game/UnityEngine/Cursor.hpp"

static bool g_menuVisible = false;
static HWND g_gameWindow = nullptr;
static WNDPROC g_originalWndProc = nullptr;

bool Overlay::Initialize(IDXGISwapChain* swapChain) {
    Logger::log("Initializing Overlay...");

    if (!DX11Device::CreateRenderTarget()) {
        Logger::error("Failed to create render target");
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    DXGI_SWAP_CHAIN_DESC desc;
    swapChain->GetDesc(&desc);
    g_gameWindow = desc.OutputWindow;

    g_originalWndProc = (WNDPROC)SetWindowLongPtr(g_gameWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

    ImGui_ImplWin32_Init(g_gameWindow);

    if (!DX11Renderer::Initialize()) {
        Logger::error("Failed to initialize DX11 renderer");
        return false;
    }

    SetupImGuiStyle();

    Logger::log("Overlay initialized successfully");
    return true;
}

void Overlay::CleanupDevice() {
    if (g_gameWindow && g_originalWndProc) {
        SetWindowLongPtr(g_gameWindow, GWLP_WNDPROC, (LONG_PTR)g_originalWndProc);
    }

    DX11Renderer::Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    DX11Device::CleanupRenderTarget();

    g_gameWindow = nullptr;
    g_originalWndProc = nullptr;
}

void Overlay::Render() {
    if (!DX11Device::GetMainRenderTargetView()) return;
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    if (UI::Render) {
        Menu::Render();
    }

    ESP::Render();

    ImGui::Render();
    DX11Renderer::Render();
}

LRESULT WINAPI Overlay::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_KEYUP && wParam == VK_DELETE) {

        UI::Render = !UI::Render;

        if (UI::Render) {
            ImGui::GetIO().MouseDrawCursor = true; //First ever written clean mouse fix for imgui LMFAO
            UnityInput::OnMenuOpened(); 
        }
        else {
            ImGui::GetIO().MouseDrawCursor = false;
            UnityInput::OnMenuClosed();
        }

        return TRUE;
    }

    if (UI::Render) {
        ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
        return TRUE;
    }

    return CallWindowProc(g_originalWndProc, hWnd, msg, wParam, lParam);

}

void Overlay::SetupImGuiStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowPadding = ImVec2(16.0f, 12.0f); 
    style.FramePadding = ImVec2(6.0f, 4.0f);
    style.ItemSpacing = ImVec2(6.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
    style.IndentSpacing = 18.0f;
    style.ScrollbarSize = 12.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.WindowRounding = 0.0f;
    style.FrameRounding = 3.0f;
    style.PopupRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.TabBorderSize = 0.0f;

    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.07f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.07f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.06f, 0.07f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.13f, 0.13f, 0.15f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.19f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.23f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.55f, 1.00f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.11f, 0.11f, 0.13f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.16f, 0.19f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.20f, 0.23f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.23f, 0.23f, 0.26f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.27f, 0.27f, 0.30f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f); 
    colors[ImGuiCol_TabActive] = colors[ImGuiCol_Tab]; 
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_Tab];
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = colors[ImGuiCol_TitleBg];
    colors[ImGuiCol_TitleBgCollapsed] = colors[ImGuiCol_TitleBg];
    colors[ImGuiCol_NavHighlight] = ImVec4(0.24f, 0.36f, 0.78f, 0.65f); 
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1, 1, 1, 0.7f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);


    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    ImFont* inter = io.Fonts->AddFontFromMemoryTTF(Inter_24ptMedium, sizeof(Inter_24ptMedium), 17.0f);
    if (inter) io.FontDefault = inter;
    io.Fonts->Build();
}

bool Overlay::IsMenuVisible() { return g_menuVisible; }
