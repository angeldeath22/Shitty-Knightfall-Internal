#include "DirectX11.hpp"
#include "../Overlay.hpp"
#include "../../utils/CMD/Logger.hpp"
#include "kiero/kiero.h"

static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_context = nullptr;
static IDXGISwapChain* g_swapChain = nullptr;

static HRESULT(__stdcall* oPresent)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
static HRESULT(__stdcall* oResizeBuffers)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

bool DirectX11::Initialize() {
    Logger::log("Initializing DirectX11...");

    if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success) {
        Logger::error("Failed to initialize kiero");
        return false;
    }

    if (kiero::bind(8, (void**)&oPresent, (void*)PresentHook) != kiero::Status::Success) {
        Logger::error("Failed to hook Present");
        return false;
    }

    if (kiero::bind(13, (void**)&oResizeBuffers, (void*)ResizeBuffersHook) != kiero::Status::Success) {
        Logger::error("Failed to hook ResizeBuffers");
        return false;
    }

    Logger::log("DirectX11 initialized successfully");
    return true;
}

void DirectX11::Shutdown() {
    Logger::log("Shutting down DirectX11...");
    CleanupDevice();
    kiero::shutdown();
}

HRESULT __stdcall DirectX11::PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
    static bool initialized = false;

    if (!initialized) {
        if (SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_device))) {
            g_device->GetImmediateContext(&g_context);
            g_swapChain = swapChain;

            Overlay::Initialize(swapChain);
            initialized = true;
            Logger::log("DirectX11 device initialized in hook");
        }
    }

    if (initialized) {
        Overlay::Render();
    }

    return oPresent(swapChain, syncInterval, flags);
}

HRESULT __stdcall DirectX11::ResizeBuffersHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
    Overlay::CleanupDevice();
    HRESULT result = oResizeBuffers(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
    if (SUCCEEDED(result)) {
        Overlay::Initialize(swapChain);
    }
    return result;
}

void DirectX11::CleanupDevice() {
    Overlay::CleanupDevice();

    if (g_context) {
        g_context->Release();
        g_context = nullptr;
    }

    if (g_device) {
        g_device->Release();
        g_device = nullptr;
    }

    g_swapChain = nullptr;
}

ID3D11Device* DirectX11::GetDevice() { return g_device; }
ID3D11DeviceContext* DirectX11::GetContext() { return g_context; }
IDXGISwapChain* DirectX11::GetSwapChain() { return g_swapChain; }