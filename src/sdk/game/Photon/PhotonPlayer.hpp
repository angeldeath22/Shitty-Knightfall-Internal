#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "il2cpp-api-types.h"

class PhotonPlayer {
public:
    PhotonPlayer(void* instance) : instance(instance) {}

    int32_t GetActorNumber();
    std::string GetNickName();
    void SetNickName(const std::string& value);
    std::string GetUserId();
    void SetUserId(const std::string& value);
    bool GetIsMasterClient();
    bool GetIsInactive();
    bool GetHasRejoined();

    std::shared_ptr<PhotonPlayer> Get(int32_t id);
    std::shared_ptr<PhotonPlayer> GetNext();
    std::shared_ptr<PhotonPlayer> GetNextFor(std::shared_ptr<PhotonPlayer> currentPlayer);
    std::shared_ptr<PhotonPlayer> GetNextFor(int32_t currentPlayerId);
    std::string ToString();
    std::string ToStringFull();

    void* GetInstance() const { return instance; }

private:
    void* instance;
};