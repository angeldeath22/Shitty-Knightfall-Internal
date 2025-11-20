#include "Application.hpp"
#include "../core/System.hpp"
#include "../render/directx/DirectX11.hpp"
#include "../utils/CMD/Logger.hpp"
#include "../update/GameLoop.hpp"
#include "../sdk/IL2CPP/il2cpp-api.hpp"
#include "../sdk/game/UnityEngine/Cursor.hpp"

Application* Application::instance = nullptr;

Application& Application::Get() {
    if (!instance) {
        instance = new Application();
    }
    return *instance;
}

bool Application::Initialize() {
    if (m_initialized) return true;

    Logger::log("Hentai-Hook Initializing...");

    if (!System::Initialize()) {
        Logger::error("Failed to initialize core system");
        return false;
    }

    if (!DirectX11::Initialize()) {
        Logger::error("Failed to initialize DirectX11");
        return false;
    }

    if (!Il2CppAPI::Initialize())
    {
        Logger::error("Failed to initialize IL2CPP");
        return false;
    }

    GameLoop::Initialize(); //cba to make this a bool
    UnityInput::Initialize(); 

    m_initialized = true;
    m_running = true;

    Logger::log("Hentai-Hook Initialized Successfully");
    return true;
}

void Application::Shutdown() {
    if (!m_initialized) return;

    Logger::log("Hentai-Hook Shutting Down...");

    m_running = false;


    DirectX11::Shutdown();
    System::Shutdown();

    m_initialized = false;

    Logger::log("Hentai-Hook Shutdown Complete");
}

void Application::Run() {
    while (m_running) {
        Sleep(10);
    }
}