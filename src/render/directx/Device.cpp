#include "Device.hpp"
#include "DirectX11.hpp"

ID3D11RenderTargetView* DX11Device::g_mainRenderTargetView = nullptr;

bool DX11Device::CreateRenderTarget() {
    IDXGISwapChain* swapChain = DirectX11::GetSwapChain();
    ID3D11Device* device = DirectX11::GetDevice();

    if (!swapChain || !device) return false;

    ID3D11Texture2D* pBackBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    device->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();

    return g_mainRenderTargetView != nullptr;
}

void DX11Device::CleanupRenderTarget() {
    if (g_mainRenderTargetView) {
        g_mainRenderTargetView->Release();
        g_mainRenderTargetView = nullptr;
    }
}

ID3D11RenderTargetView* DX11Device::GetMainRenderTargetView() {
    return g_mainRenderTargetView;
}