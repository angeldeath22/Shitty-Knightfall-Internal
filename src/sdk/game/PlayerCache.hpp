#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <math.hpp>
#include "Photon/PhotonPlayer.hpp"
#include "Game/GamePlayer.hpp"
#include "Photon/PhotonView.hpp"

struct CachedPlayer {
    std::shared_ptr<PhotonPlayer> photonPlayer;
    std::shared_ptr<GamePlayer> gamePlayer;
    std::shared_ptr<PlayerData> playerData;
    std::shared_ptr<PhotonView> photonView;
    std::string name;
    std::string userId;
    int32_t actorNumber;
    uint64_t teamId;
    bool isMasterClient;
    bool isLocalPlayer;
    Vector3 position;
    Vector3 headPosition;
    float health;


    bool isReloading;
    float reloadProgress;
    int totalAmmo;
    int bulletsLoaded;
    bool isGrounded;
    bool isCrouching;
    float currentSpread;
    float speedM;
    bool isGhost;
    int currentBombs;
    int currentBandage;
    int currentWeaponID;
    int jumps;
    int jumpsUsed;
    float currentHealthPercentage;
    int armorIndex;
    bool isCharging;
    float currentCharge;

    bool isValid;
    uint64_t lastUpdateTime;

    CachedPlayer() : actorNumber(0), teamId(0), isMasterClient(false), isLocalPlayer(false),
        health(0.0f), isReloading(false), reloadProgress(0.0f), totalAmmo(0), bulletsLoaded(0),
        isGrounded(false), isCrouching(false), currentSpread(0.0f), speedM(0.0f), isGhost(false),
        currentBombs(0), currentBandage(0), currentWeaponID(0), jumps(0), jumpsUsed(0),
        currentHealthPercentage(0.0f), armorIndex(0), isCharging(false), currentCharge(0.0f),
        isValid(false), lastUpdateTime(0) {
    }
};

class PlayerCache {
public:
    static PlayerCache& GetInstance() {
        static PlayerCache instance;
        return instance;
    }

    void UpdateCache();
    void ClearInvalidPlayers();
    void ClearCache();
    void AddPlayerFromHook(std::shared_ptr<GamePlayer> player);
    std::vector<std::shared_ptr<CachedPlayer>> GetPlayers();
    std::shared_ptr<CachedPlayer> GetPlayerByActorNumber(int32_t actorNumber);
    std::shared_ptr<CachedPlayer> GetLocalPlayer();
    std::vector<std::shared_ptr<CachedPlayer>> GetEnemyPlayers();
    std::vector<std::shared_ptr<CachedPlayer>> GetTeammates();

private:
    PlayerCache() = default;
    ~PlayerCache() = default;

    std::unordered_map<int32_t, std::shared_ptr<CachedPlayer>> players;
    std::mutex cacheMutex;
    std::shared_ptr<CachedPlayer> localPlayer;

    std::vector<std::shared_ptr<GamePlayer>> FindAllGamePlayers();
    std::shared_ptr<PhotonView> GetPhotonViewFromGamePlayer(std::shared_ptr<GamePlayer> gamePlayer);
    void ProcessObjectArray(void* objectArray, std::vector<std::shared_ptr<GamePlayer>>& result);

    std::vector<std::shared_ptr<GamePlayer>> FindPlayersDirectly();
    void FindOtherPlayers(std::shared_ptr<GamePlayer> localPlayer, std::vector<std::shared_ptr<GamePlayer>>& result);
};