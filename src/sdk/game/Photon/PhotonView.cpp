#include "PhotonView.hpp"


std::shared_ptr<PhotonView> PhotonView::Get(void* component) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0x15E4790);
    auto result = func(component, nullptr);
    return result ? std::make_shared<PhotonView>(result) : nullptr;
}

std::shared_ptr<PhotonView> PhotonView::Get(std::shared_ptr<void> gameObject) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0x15E4710);
    auto result = func(gameObject.get(), nullptr);
    return result ? std::make_shared<PhotonView>(result) : nullptr;
}

std::shared_ptr<PhotonView> PhotonView::Find(int32_t viewID) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(int32_t, void*)>(base + 0x15E46C0);
    auto result = func(viewID, nullptr);
    return result ? std::make_shared<PhotonView>(result) : nullptr;
}

int32_t PhotonView::GetOwnerActorNr() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0x15E6620);
    return func(instance, nullptr);
}

int32_t PhotonView::GetViewID() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0x1162EA0);
    return func(instance, nullptr);
}

bool PhotonView::GetIsMine() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0x584520);
    return func(instance, nullptr);
}

bool PhotonView::GetAmOwner() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<bool(__stdcall*)(void*, void*)>(base + 0x823640);
    return func(instance, nullptr);
}

std::shared_ptr<PhotonPlayer> PhotonView::GetOwner() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0x4F9270);
    auto result = func(instance, nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

std::shared_ptr<PhotonPlayer> PhotonView::GetController() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void* (__stdcall*)(void*, void*)>(base + 0x4EAE90);
    auto result = func(instance, nullptr);
    return result ? std::make_shared<PhotonPlayer>(result) : nullptr;
}

void PhotonView::RequestOwnership() {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*)>(base + 0x15E4E60);
    func(instance, nullptr);
}

void PhotonView::TransferOwnership(std::shared_ptr<PhotonPlayer> newOwner) {
    if (!newOwner) return;
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, void*, void*)>(base + 0x15E5EB0);
    func(instance, newOwner->GetInstance(), nullptr);
}

void PhotonView::TransferOwnership(int32_t newOwnerId) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
    auto func = reinterpret_cast<void(__stdcall*)(void*, int32_t, void*)>(base + 0x15E5910);
    func(instance, newOwnerId, nullptr);
}