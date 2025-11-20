#pragma once
#include <memory>
#include <windows.h>

class Application {
private:
    static Application* instance;
    bool m_initialized = false;
    bool m_running = false;

public:
    static Application& Get();

    bool Initialize();
    void Shutdown();
    void Run();

    bool IsRunning() const { return m_running; }
    void RequestShutdown() { m_running = false; }

private:
    Application() = default;
    ~Application() = default;
};