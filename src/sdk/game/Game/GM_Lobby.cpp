#include "GM_Lobby.hpp"
#include <iostream>

std::shared_ptr<GM_Lobby> GM_Lobby::GetStaticInstance() {
    try {
        auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));

        
        auto getInstanceFunc = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0x639160); 

        void* instance = getInstanceFunc(nullptr);
        if (instance) {
            std::cout << "[DEBUG] GM_Lobby instance found: " << instance << std::endl;
            return std::make_shared<GM_Lobby>(instance);
        }
    }
    catch (...) {
        std::cout << "[DEBUG] GM_Lobby::GetInstance failed" << std::endl;
    }
    return nullptr;
}