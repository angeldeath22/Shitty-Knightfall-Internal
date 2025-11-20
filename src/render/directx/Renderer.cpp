#include "Renderer.hpp"
#include "DirectX11.hpp"
#include "Device.hpp"
#include "../../utils/CMD/Logger.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"

bool DX11Renderer::Initialize() {
    Logger::log("Initializing DX11 Renderer...");
    return CreateDeviceObjects();
}

void DX11Renderer::Shutdown() {
    Logger::log("Shutting down DX11 Renderer...");
    CleanupDeviceObjects();
}

void DX11Renderer::Render() {
    ID3D11DeviceContext* context = DirectX11::GetContext();
    ID3D11RenderTargetView* renderTarget = DX11Device::GetMainRenderTargetView();
    if (context && renderTarget) {
        context->OMSetRenderTargets(1, &renderTarget, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}

bool DX11Renderer::CreateDeviceObjects() {
    if (!DirectX11::GetDevice()) return false;

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    return ImGui_ImplDX11_Init(DirectX11::GetDevice(), DirectX11::GetContext());
}

void DX11Renderer::CleanupDeviceObjects() {
    ImGui_ImplDX11_Shutdown();
}