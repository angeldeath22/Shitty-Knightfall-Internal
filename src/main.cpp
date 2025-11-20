#include <windows.h>
#include "core/Application.hpp"
#include "utils/CMD/Logger.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);

        CreateThread(nullptr, 0, [](LPVOID) -> DWORD {
            Logger::INIT_CMD();

            auto& app = Application::Get();
            if (app.Initialize()) {
                app.Run();
            }
            app.Shutdown();

            return 0;
            }, nullptr, 0, nullptr);
    }
    return TRUE;
}