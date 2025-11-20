#pragma once

class DX11Renderer {
public:
    static bool Initialize();
    static void Shutdown();
    static void Render();

private:
    static bool CreateDeviceObjects();
    static void CleanupDeviceObjects();
};