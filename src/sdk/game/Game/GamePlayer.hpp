#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "il2cpp-api-types.h"
#include <math.hpp>
#include "../PlayerData.hpp"

class GamePlayer {
public:
    GamePlayer(void* instance) : instance(instance) {}

    uint64_t GetTeamID();
    void SetTeamID(uint64_t value);

    void SetRotation(Vector3 localEulerAngles);
    void AssignArmor(int32_t armorIndex);
    void Killed(std::shared_ptr<GamePlayer> killed);
    void AssignTeam(uint64_t team);
    int32_t GetPrimaryColour();
    void AssignColour(int32_t colour);
    float GetDamageMultiplier();
    void Heal(float healing, bool networked);
    bool IsLocalPlayer();
    void FixedUpdate();
    void Update();
    float GetCurrentHealth();
    Vector3 GetHeadPos();

    std::shared_ptr<void> GetGameObject();
    std::shared_ptr<void> GetTransform();


    std::shared_ptr<PlayerData> GetPlayerData();

    void* GetInstance() const { return instance; }

private:
    void* instance;
};