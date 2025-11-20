#pragma once
#include <d3d11.h>

class DX11Device {
public:
    static bool CreateRenderTarget();
    static void CleanupRenderTarget();
    static ID3D11RenderTargetView* GetMainRenderTargetView();

private:
    static ID3D11RenderTargetView* g_mainRenderTargetView;
};