#pragma once
#include <d3d11.h>
#include <windows.h>

class DirectX11 {
public:
    static bool Initialize();
    static void Shutdown();

    static ID3D11Device* GetDevice();
    static ID3D11DeviceContext* GetContext();
    static IDXGISwapChain* GetSwapChain();

private:
    static void CleanupDevice();

    static HRESULT __stdcall PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
    static HRESULT __stdcall ResizeBuffersHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
};