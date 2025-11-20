#include "PhotonServerConnector.hpp"
#include "../../funcs.hpp"
//#include "il2cpp-utils.h"

std::shared_ptr<PhotonServerConnector> PhotonServerConnector::GetStaticInstance() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));


    auto getInstanceFunc = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0x7FBBF0);

    void* instance = getInstanceFunc(nullptr);
    return instance ? std::make_shared<PhotonServerConnector>(instance) : nullptr;
}
std::string PhotonServerConnector::GetPlayerName() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));


    auto getPlayerNameFunc = reinterpret_cast<Il2CppString * (__stdcall*)(void*)>(base + 0x7FBC30);

    Il2CppString* result = getPlayerNameFunc(nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

void PhotonServerConnector::SetPlayerName(const std::string& name) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));


    auto setPlayerNameFunc = reinterpret_cast<void(__stdcall*)(Il2CppString*, void*)>(base + 0x7FBD00);

    Il2CppString* il2cppName = WriteIl2CppString(name.c_str());
    if (il2cppName) {
        setPlayerNameFunc(il2cppName, nullptr);
    }
}

std::string PhotonServerConnector::GetUserID() {
    if (!instance) return "";

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));

    auto getUserIDFunc = reinterpret_cast<Il2CppString * (__stdcall*)(void*, void*)>(base + 0x7F93D0);

    Il2CppString* result = getUserIDFunc(instance, nullptr);
    return result ? Il2CppStringToStdString(result) : "";
}

int32_t PhotonServerConnector::GetUserColour() {
    if (!instance) return 0;

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));

    
    auto getUserColourFunc = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0x7F93C0);

    return getUserColourFunc(instance, nullptr);
}

int32_t PhotonServerConnector::GetUserArmor() {
    if (!instance) return 0;

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));


    auto getUserArmorFunc = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0x7F93B0);

    return getUserArmorFunc(instance, nullptr);
}