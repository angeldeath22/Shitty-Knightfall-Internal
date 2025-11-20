#include "GamePlayer.hpp"

std::shared_ptr<PlayerData> GamePlayer::GetPlayerData() {
    if (!instance) return nullptr;

    try {
        void* playerDataInstance = SafeGetField<void*>(instance, 0x68, nullptr);

        if (playerDataInstance && IsValidPointer(playerDataInstance)) {
            return std::make_shared<PlayerData>(playerDataInstance);
        }

        return nullptr;
    }
    catch (...) {
        return nullptr;
    }
}

uint64_t GamePlayer::GetTeamID() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<uint64_t(__stdcall*)(void*, void*)>(base + 0x3734F0);
    return func(instance, nullptr);
}

void GamePlayer::SetTeamID(uint64_t value) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, uint64_t, void*)>(base + 0x4EAEC0);
    func(instance, value, nullptr);
}

void GamePlayer::SetRotation(Vector3 localEulerAngles) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, Vector3, void*)>(base + 0x273A10);
    func(instance, localEulerAngles, nullptr);
}

void GamePlayer::AssignArmor(int32_t armorIndex) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, int32_t, void*)>(base + 0x809480);
    func(instance, armorIndex, nullptr);
}

void GamePlayer::Killed(std::shared_ptr<GamePlayer> killed) {
    if (!killed) return;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*, void*)>(base + 0x80AF70);
    func(instance, killed->GetInstance(), nullptr);
}

void GamePlayer::AssignTeam(uint64_t team) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, uint64_t, void*)>(base + 0x4EAEC0);
    func(instance, team, nullptr);
}

int32_t GamePlayer::GetPrimaryColour() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0x80AD30);
    return func(instance, nullptr);
}

void GamePlayer::AssignColour(int32_t colour) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, int32_t, void*)>(base + 0x8094A0);
    func(instance, colour, nullptr);
}

float GamePlayer::GetDamageMultiplier() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<float(__stdcall*)(void*, void*)>(base + 0x80ACA0);
    return func(instance, nullptr);
}

void GamePlayer::Heal(float healing, bool networked) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, float, bool, void*)>(base + 0x80AD50);
    func(instance, healing, networked, nullptr);
}

bool GamePlayer::IsLocalPlayer() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0x80AEF0);
    return func(instance, nullptr);
}

void GamePlayer::FixedUpdate() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*)>(base + 0x80AB10);
    func(instance, nullptr);
}

void GamePlayer::Update() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*)>(base + 0x80C2A0);
    func(instance, nullptr);
}

float GamePlayer::GetCurrentHealth() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<float(__stdcall*)(void*, void*)>(base + 0x80AC50);
    return func(instance, nullptr);
}

Vector3 GamePlayer::GetHeadPos() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<Vector3(__stdcall*)(void*, void*)>(base + 0x80ACD0);
    return func(instance, nullptr);
}

std::shared_ptr<void> GamePlayer::GetGameObject() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0xD80AA0);
    auto result = func(instance, nullptr);
    return result ? std::make_shared<void*>(result) : nullptr;
}

std::shared_ptr<void> GamePlayer::GetTransform() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0xD80AE0);
    auto result = func(instance, nullptr);
    return result ? std::make_shared<void*>(result) : nullptr;
}