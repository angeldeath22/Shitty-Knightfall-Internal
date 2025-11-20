#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include "il2cpp-api-types.h"
#include <math.hpp>

class PhotonPlayer;

class PhotonNetwork {
public:

    static std::string GetServerAddress();
    static void* GetCurrentLobby();
    static void* GetCurrentRoom();
    static std::shared_ptr<PhotonPlayer> GetLocalPlayer();
    static std::string GetNickName();
    static void SetNickName(const std::string& value);
    static std::vector<std::shared_ptr<PhotonPlayer>> GetPlayerList();
    static std::vector<std::shared_ptr<PhotonPlayer>> GetPlayerListOthers();
    static bool GetInLobby();
    static bool GetIsMasterClient();
    static std::shared_ptr<PhotonPlayer> GetMasterClient();
    static bool GetInRoom();
    static int32_t GetCountOfPlayers();

    static bool CloseConnection(std::shared_ptr<PhotonPlayer> kickPlayer);
    static bool SetMasterClient(std::shared_ptr<PhotonPlayer> masterClientPlayer);
    static std::shared_ptr<void> Instantiate(const std::string& prefabName, Vector3 position, Quaternion rotation, uint8_t group, void* data);
    static std::shared_ptr<void> Instantiate(Il2CppString* prefabName, Vector3 position, Quaternion rotation, uint8_t group, void* data);
    static void Destroy(void* targetView);
    static void Destroy(std::shared_ptr<void> targetGo);
    static void DestroyPlayerObjects(std::shared_ptr<PhotonPlayer> targetPlayer);
    static void DestroyPlayerObjects(int32_t targetPlayerId);
    static void DestroyAll();

private:
    static uintptr_t GetBaseAddress();
};