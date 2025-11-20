#include "PhotonPlayer.hpp"
#include "../../funcs.hpp"
//#include "il2cpp-utils.h"

int32_t PhotonPlayer::GetActorNumber() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0x49BEB0);
    return func(instance, nullptr);
}

std::string PhotonPlayer::GetNickName() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<Il2CppString * (__stdcall*)(void*, void*)>(base + 0x49BEE0);
    auto result = func(instance, nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

void PhotonPlayer::SetNickName(const std::string& value) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, Il2CppString*, void*)>(base + 0x15BBF20);
    Il2CppString* il2cppValue = WriteIl2CppString(value.c_str());
    if (il2cppValue) {
        func(instance, il2cppValue, nullptr);
    }
}

std::string PhotonPlayer::GetUserId() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<Il2CppString * (__stdcall*)(void*, void*)>(base + 0x373540);
    auto result = func(instance, nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

void PhotonPlayer::SetUserId(const std::string& value) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, Il2CppString*, void*)>(base + 0x3735A0);
    Il2CppString* il2cppValue = WriteIl2CppString(value.c_str());
    if (il2cppValue) {
        func(instance, il2cppValue, nullptr);
    }
}

bool PhotonPlayer::GetIsMasterClient() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0x15BBEF0);
    return func(instance, nullptr);
}

bool PhotonPlayer::GetIsInactive() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0x373500);
    return func(instance, nullptr);
}

bool PhotonPlayer::GetHasRejoined() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0x15BBEE0);
    return func(instance, nullptr);
}

std::shared_ptr<PhotonPlayer> PhotonPlayer::Get(int32_t id) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, int32_t, void*)>(base + 0x15BB500);
    auto result = func(instance, id, nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

std::shared_ptr<PhotonPlayer> PhotonPlayer::GetNext() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0x15BB4F0);
    auto result = func(instance, nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

std::shared_ptr<PhotonPlayer> PhotonPlayer::GetNextFor(std::shared_ptr<PhotonPlayer> currentPlayer) {
    if (!currentPlayer) return nullptr;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*, void*)>(base + 0x15BB2F0);
    auto result = func(instance, currentPlayer->GetInstance(), nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

std::shared_ptr<PhotonPlayer> PhotonPlayer::GetNextFor(int32_t currentPlayerId) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, int32_t, void*)>(base + 0x15BB310);
    auto result = func(instance, currentPlayerId, nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

std::string PhotonPlayer::ToString() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<Il2CppString * (__stdcall*)(void*, void*)>(base + 0x15BBCB0);
    auto result = func(instance, nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

std::string PhotonPlayer::ToStringFull() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<Il2CppString * (__stdcall*)(void*, void*)>(base + 0x15BBA30);
    auto result = func(instance, nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}