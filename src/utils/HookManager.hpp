#pragma once
#include <polyhook2/Detour/x64Detour.hpp>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <cstdint>

class HookManager
{
public:
    static HookManager* Get();

    template<typename Fn>
    bool AddInline(void* target, Fn detour, Fn& original)
    {
        std::scoped_lock lock(hookMutex);

        if (hooks.find(target) != hooks.end())
            return false;

        HookEntry entry{};
        entry.target = target;
        entry.detourFunc = reinterpret_cast<void*>(detour);

        uint64_t trampoline = 0;
        entry.detour = std::make_unique<PLH::x64Detour>(
            reinterpret_cast<uint64_t>(target),
            reinterpret_cast<uint64_t>(detour),
            &trampoline
        );

        if (!entry.detour->hook())
            return false;

        original = reinterpret_cast<Fn>(trampoline);

        entry.enabled = true;
        hooks[target] = std::move(entry);
        return true;
    }

    bool Remove(void* target);
    bool Enable(void* target);
    bool Disable(void* target);

private:
    struct HookEntry
    {
        void* target = nullptr;
        void* detourFunc = nullptr;
        std::unique_ptr<PLH::x64Detour> detour;
        bool enabled = false;
    };

    std::unordered_map<void*, HookEntry> hooks;
    std::mutex hookMutex;

    HookManager() = default;
};