#include "GameLoop.hpp"
#include "../utils/CMD/Logger.hpp"
#include "../sdk/game/PlayerCache.hpp"
#include "../utils/HookManager.hpp"

typedef void(__fastcall* tPlayerUpdateOriginal)(void* thisPtr);
static tPlayerUpdateOriginal PlayerUpdateOriginal = nullptr;
void __fastcall PlayerUpdateHook(void* thisPtr) {
    PlayerUpdateOriginal(thisPtr);

    try {
        auto gamePlayer = std::make_shared<GamePlayer>(thisPtr);
        PlayerCache::GetInstance().AddPlayerFromHook(gamePlayer);
    }
    catch (...) {

    }


    static uint64_t lastUpdate = 0;
    if (GetTickCount64() - lastUpdate > 100) { 
        try {
            PlayerCache::GetInstance().UpdateCache();
            lastUpdate = GetTickCount64();
        }
        catch (...) {

        }
    }
}




void GameLoop::Initialize() {
    uintptr_t gameAsm = 0;
    while (!(gameAsm = (uintptr_t)GetModuleHandleA("GameAssembly.dll"))) Sleep(100);

    void* target = reinterpret_cast<void*>(gameAsm + 0x80AB10); // RVA: [0x80AB10] void FixedUpdate()

    HookManager* pHookManager = HookManager::Get();

    pHookManager->AddInline<tPlayerUpdateOriginal>(target, PlayerUpdateHook, PlayerUpdateOriginal);

}

