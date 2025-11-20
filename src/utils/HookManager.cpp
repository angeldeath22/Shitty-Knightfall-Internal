#include "HookManager.hpp"

HookManager* HookManager::Get()
{
    static HookManager instance;
    return &instance;
}

bool HookManager::Remove(void* target)
{
    std::scoped_lock lock(hookMutex);
    auto it = hooks.find(target);
    if (it == hooks.end())
        return false;
    it->second.detour->unHook();
    hooks.erase(it);
    return true;
}

bool HookManager::Enable(void* target)
{
    std::scoped_lock lock(hookMutex);
    auto it = hooks.find(target);
    if (it == hooks.end())
        return false;
    return it->second.detour->hook();
}

bool HookManager::Disable(void* target)
{
    std::scoped_lock lock(hookMutex);
    auto it = hooks.find(target);
    if (it == hooks.end())
        return false;
    return it->second.detour->unHook();
}
