#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include <vector>
#include "il2cpp-api-types.h"
#include "Game/GamePlayer.hpp"

class PlayerHandler {
public:
    PlayerHandler(void* instance) : instance(instance) {}


    static std::shared_ptr<PlayerHandler> GetStaticInstance();
    static std::shared_ptr<GamePlayer> GetLocalPlayer();

    std::vector<std::shared_ptr<GamePlayer>> GetCurrentPlayers();


    std::shared_ptr<GamePlayer> GetTeamMate();
    void AddPlayer(std::shared_ptr<GamePlayer> player);
    void RemovePlayer(std::shared_ptr<GamePlayer> player);
    void ChangePlayerTeam(std::shared_ptr<GamePlayer> player, uint64_t newTeam);

    void* GetInstance() const { return instance; }

private:
    void* instance;
};