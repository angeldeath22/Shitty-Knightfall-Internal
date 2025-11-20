#include "PlayerHandler.hpp"
#include <iostream>

#include "PlayerHandler.hpp"
#include <iostream>

#include "PlayerHandler.hpp"
#include <iostream>

std::shared_ptr<PlayerHandler> PlayerHandler::GetStaticInstance() {
    std::cout << "[DEBUG] PlayerHandler::GetInstance disabled (causing crash)" << std::endl;
    return nullptr;
}

std::shared_ptr<GamePlayer> PlayerHandler::GetLocalPlayer() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));

    auto getLocalPlayerFunc = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0x80AEF0);

    void* localPlayer = getLocalPlayerFunc(nullptr);
    if (localPlayer) {
        std::cout << "[SUCCESS] Local player found: " << localPlayer << std::endl;
        return std::make_shared<GamePlayer>(localPlayer);
    }

    return nullptr;
}


std::vector<std::shared_ptr<GamePlayer>> PlayerHandler::GetCurrentPlayers() {

    std::cout << "[DEBUG] GetCurrentPlayers disabled" << std::endl;
    return std::vector<std::shared_ptr<GamePlayer>>();
}


std::shared_ptr<GamePlayer> PlayerHandler::GetTeamMate() {
    if (!instance) return nullptr;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto getTeamMateFunc = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0x518D80);
    void* playerInstance = getTeamMateFunc(nullptr);
    return playerInstance ? std::make_shared<GamePlayer>(playerInstance) : nullptr;
}

void PlayerHandler::AddPlayer(std::shared_ptr<GamePlayer> player) {
    if (!instance || !player) return;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto addPlayerFunc = reinterpret_cast<void(__stdcall*)(void*, void*, void*)>(base + 0x5184C0);
    addPlayerFunc(instance, player->GetInstance(), nullptr);
}

void PlayerHandler::RemovePlayer(std::shared_ptr<GamePlayer> player) {
    if (!instance || !player) return;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto removePlayerFunc = reinterpret_cast<void(__stdcall*)(void*, void*, void*)>(base + 0x519150);
    removePlayerFunc(instance, player->GetInstance(), nullptr);
}

void PlayerHandler::ChangePlayerTeam(std::shared_ptr<GamePlayer> player, uint64_t newTeam) {
    if (!instance || !player) return;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto changeTeamFunc = reinterpret_cast<void(__stdcall*)(void*, void*, uint64_t, void*)>(base + 0x5187B0);
    changeTeamFunc(instance, player->GetInstance(), newTeam, nullptr);
}