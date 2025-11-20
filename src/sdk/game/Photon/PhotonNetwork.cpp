#include "PhotonNetwork.hpp"
#include "PhotonPlayer.hpp"
#include <Windows.h>
#include "../../funcs.hpp"


uintptr_t PhotonNetwork::GetBaseAddress() {
    return reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
}

std::string PhotonNetwork::GetServerAddress() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<Il2CppString * (__stdcall*)(void*)>(base + 0xB79010);
    auto result = func(nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

void* PhotonNetwork::GetCurrentLobby() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xB775F0);
    return func(nullptr);
}

void* PhotonNetwork::GetCurrentRoom() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xB77660);
    return func(nullptr);
}

std::shared_ptr<PhotonPlayer> PhotonNetwork::GetLocalPlayer() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xB77F10);
    auto result = func(nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

std::string PhotonNetwork::GetNickName() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<Il2CppString * (__stdcall*)(void*)>(base + 0xB78430);
    auto result = func(nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

void PhotonNetwork::SetNickName(const std::string& value) {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void(__stdcall*)(Il2CppString*, void*)>(base + 0xB7A000);
    Il2CppString* il2cppValue = WriteIl2CppString(value.c_str());
    if (il2cppValue) {
        func(il2cppValue, nullptr);
    }
}

std::vector<std::shared_ptr<PhotonPlayer>> PhotonNetwork::GetPlayerList() {
    std::vector<std::shared_ptr<PhotonPlayer>> players;
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xB78C10);
    auto* array = func(nullptr);
    if (!array) return players;

    auto lengthFunc = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0xE71910);
    auto getValueFunc = reinterpret_cast<void* (__stdcall*)(void*, int32_t, void*)>(base + 0xE70AD0);

    int32_t len = lengthFunc(array, nullptr);
    for (int32_t i = 0; i < len; ++i) {
        auto* player = getValueFunc(array, i, nullptr);
        if (player) {
            players.emplace_back(std::make_shared<PhotonPlayer>(player));
        }
    }
    return players;
}

std::vector<std::shared_ptr<PhotonPlayer>> PhotonNetwork::GetPlayerListOthers() {
    std::vector<std::shared_ptr<PhotonPlayer>> players;
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xB78940);
    auto* array = func(nullptr);
    if (!array) return players;

    auto lengthFunc = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0xE71910);
    auto getValueFunc = reinterpret_cast<void* (__stdcall*)(void*, int32_t, void*)>(base + 0xE70AD0);

    int32_t len = lengthFunc(array, nullptr);
    for (int32_t i = 0; i < len; ++i) {
        auto* player = getValueFunc(array, i, nullptr);
        if (player) {
            players.emplace_back(std::make_shared<PhotonPlayer>(player));
        }
    }
    return players;
}

bool PhotonNetwork::GetInLobby() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<bool(__stdcall*)(void*)>(base + 0xB77830);
    return func(nullptr);
}

bool PhotonNetwork::GetIsMasterClient() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<bool(__stdcall*)(void*)>(base + 0xB77B10);
    return func(nullptr);
}

std::shared_ptr<PhotonPlayer> PhotonNetwork::GetMasterClient() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xB77FB0);
    auto result = func(nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

bool PhotonNetwork::GetInRoom() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<bool(__stdcall*)(void*)>(base + 0xB778A0);
    return func(nullptr);
}

int32_t PhotonNetwork::GetCountOfPlayers() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<int32_t(__stdcall*)(void*)>(base + 0xB773F0);
    return func(nullptr);
}

bool PhotonNetwork::CloseConnection(std::shared_ptr<PhotonPlayer> kickPlayer) {
    if (!kickPlayer) return false;
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0xB5DCE0);
    return func(kickPlayer->GetInstance(), nullptr);
}

bool PhotonNetwork::SetMasterClient(std::shared_ptr<PhotonPlayer> masterClientPlayer) {
    if (!masterClientPlayer) return false;
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0xB74F60);
    return func(masterClientPlayer->GetInstance(), nullptr);
}

std::shared_ptr<void> PhotonNetwork::Instantiate(const std::string& prefabName, Vector3 position, Quaternion rotation, uint8_t group, void* data) {
    Il2CppString* il2cppPrefab = WriteIl2CppString(prefabName.c_str());
    return Instantiate(il2cppPrefab, position, rotation, group, data);
}

std::shared_ptr<void> PhotonNetwork::Instantiate(Il2CppString* prefabName, Vector3 position, Quaternion rotation, uint8_t group, void* data) {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void* (__stdcall*)(Il2CppString*, Vector3, Quaternion, uint8_t, void*, void*)>(base + 0xB64160);
    auto* result = func(prefabName, position, rotation, group, data, nullptr);
    return result ? std::make_shared<void*>(result) : nullptr;
}

void PhotonNetwork::Destroy(void* targetView) {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*)>(base + 0xB60D60);
    func(targetView, nullptr);
}

void PhotonNetwork::Destroy(std::shared_ptr<void> targetGo) {
    if (!targetGo) return;
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*)>(base + 0xB60CB0);
    func(targetGo.get(), nullptr);
}

void PhotonNetwork::DestroyPlayerObjects(std::shared_ptr<PhotonPlayer> targetPlayer) {
    if (!targetPlayer) return;
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*)>(base + 0xB60320);
    func(targetPlayer->GetInstance(), nullptr);
}

void PhotonNetwork::DestroyPlayerObjects(int32_t targetPlayerId) {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void(__stdcall*)(int32_t, void*)>(base + 0xB603D0);
    func(targetPlayerId, nullptr);
}

void PhotonNetwork::DestroyAll() {
    auto base = GetBaseAddress();
    auto func = reinterpret_cast<void(__stdcall*)(void*)>(base + 0xB60000);
    func(nullptr);
}