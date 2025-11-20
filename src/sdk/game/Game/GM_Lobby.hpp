#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "il2cpp-api-types.h"
#include "GamePlayer.hpp"

class GM_Lobby {
public:
    GM_Lobby(void* instance) : instance(instance) {}

    static std::shared_ptr<GM_Lobby> GetStaticInstance();

    void PlayerSpawned(void* player);
    void PlayerDied(void* player);

    void* GetInstance() const { return instance; }

private:
    void* instance;
};