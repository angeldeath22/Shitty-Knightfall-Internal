#include "PlayerCache.hpp"
#include <chrono>
#include <Windows.h>
#include "Photon/PhotonNetwork.hpp"
#include <iostream>
#include "PlayerHandler.hpp"

std::shared_ptr<PhotonView> PlayerCache::GetPhotonViewFromGamePlayer(std::shared_ptr<GamePlayer> gamePlayer) {
    if (!gamePlayer) return nullptr;

    auto gameObject = gamePlayer->GetGameObject();
    if (!gameObject) return nullptr;

    return PhotonView::Get(gameObject);
}

std::vector<std::shared_ptr<GamePlayer>> PlayerCache::FindAllGamePlayers() {
    return FindPlayersDirectly();
}

void PlayerCache::FindOtherPlayers(std::shared_ptr<GamePlayer> localPlayer, std::vector<std::shared_ptr<GamePlayer>>& result) {
    
    try {
        auto photonPlayers = PhotonNetwork::GetPlayerList();
        std::cout << "[DEBUG] Photon players: " << photonPlayers.size() << std::endl;


        for (auto& photonPlayer : photonPlayers) {
            if (photonPlayer) {
                int32_t actorNumber = photonPlayer->GetActorNumber();
                if (actorNumber != localPlayer->GetTeamID()) { 

                }
            }
        }
    }
    catch (...) {
        std::cout << "[DEBUG] Photon method failed" << std::endl;
    }
}

static std::vector<std::shared_ptr<GamePlayer>> g_hookDiscoveredPlayers;
static std::mutex g_playerMutex;

std::vector<std::shared_ptr<GamePlayer>> PlayerCache::FindPlayersDirectly() {
    std::lock_guard<std::mutex> lock(g_playerMutex);

    std::cout << "[DEBUG] Hook players count: " << g_hookDiscoveredPlayers.size() << std::endl;


    for (int i = 0; i < g_hookDiscoveredPlayers.size(); i++) {
        auto player = g_hookDiscoveredPlayers[i];
        if (player) {
            try {
                float health = player->GetCurrentHealth();
                bool isLocal = player->IsLocalPlayer();
                std::cout << "[DEBUG] Player " << i << ": " << player->GetInstance()
                    << " Health: " << health << " Local: " << isLocal << std::endl;
            }
            catch (...) {
                std::cout << "[DEBUG] Player " << i << ": " << player->GetInstance() << " (invalid)" << std::endl;
            }
        }
    }

    return g_hookDiscoveredPlayers;
}

void PlayerCache::ProcessObjectArray(void* objectArray, std::vector<std::shared_ptr<GamePlayer>>& result) {
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));

    auto getLengthFunc = reinterpret_cast<int32_t(__stdcall*)(void*, void*)>(base + 0xE70A30);
    int32_t length = getLengthFunc(objectArray, nullptr);

    if (length <= 0) return;


    auto getValueFunc = reinterpret_cast<void* (__stdcall*)(void*, int32_t, void*)>(base + 0xE71350);

    for (int32_t i = 0; i < length; i++) {
        void* playerInstance = getValueFunc(objectArray, i, nullptr);
        if (playerInstance) {
            result.emplace_back(std::make_shared<GamePlayer>(playerInstance));
        }
    }
}

void PlayerCache::AddPlayerFromHook(std::shared_ptr<GamePlayer> player) {
    if (!player) return;

    std::lock_guard<std::mutex> lock(g_playerMutex);


    for (auto& existing : g_hookDiscoveredPlayers) {
        if (existing && existing->GetInstance() == player->GetInstance()) {
            return; 
        }
    }


    try {
        float health = player->GetCurrentHealth();
        if (health >= 0 && health <= 200) { 
            g_hookDiscoveredPlayers.push_back(player);
            std::cout << "[SUCCESS] Hook added player: " << player->GetInstance()
                << " Health: " << health
                << " Local: " << player->IsLocalPlayer()
                << " (Total: " << g_hookDiscoveredPlayers.size() << ")" << std::endl;
        }
    }
    catch (...) {
        std::cout << "[DEBUG] Invalid player object: " << player->GetInstance() << std::endl;
    }
}

void PlayerCache::ClearInvalidPlayers() {
    std::lock_guard<std::mutex> lock(g_playerMutex);


    g_hookDiscoveredPlayers.erase(
        std::remove_if(g_hookDiscoveredPlayers.begin(), g_hookDiscoveredPlayers.end(),
            [](const std::shared_ptr<GamePlayer>& player) {
                if (!player) return true;
                try {
                    player->GetCurrentHealth(); 
                    return false;
                }
                catch (...) {
                    return true; 
                }
            }),
        g_hookDiscoveredPlayers.end()
    );
}

void PlayerCache::UpdateCache() {
    std::lock_guard<std::mutex> lock(cacheMutex);

    try {
        auto allPlayers = FindPlayersDirectly();
        auto currentTime = GetTickCount64();

        std::unordered_map<int32_t, std::shared_ptr<CachedPlayer>> newPlayers;

        for (int i = 0; i < allPlayers.size(); i++) {
            auto& gamePlayer = allPlayers[i];
            if (!gamePlayer) continue;

            try {
                auto playerData = gamePlayer->GetPlayerData();

                bool found = false;
                for (auto& [oldKey, oldPlayer] : players) {
                    if (oldPlayer->gamePlayer->GetInstance() == gamePlayer->GetInstance()) {
                        oldPlayer->health = gamePlayer->GetCurrentHealth();
                        oldPlayer->teamId = gamePlayer->GetTeamID();
                        oldPlayer->headPosition = gamePlayer->GetHeadPos();
                        oldPlayer->lastUpdateTime = currentTime;
                        oldPlayer->isValid = true;

                        if (playerData) {
                            oldPlayer->isReloading = playerData->GetIsReloading();
                            oldPlayer->reloadProgress = playerData->GetReloadingProgress();
                            oldPlayer->totalAmmo = playerData->GetTotalAmmo();
                            oldPlayer->bulletsLoaded = playerData->GetBulletsLoaded();
                            oldPlayer->isGrounded = playerData->GetIsGrounded();
                            oldPlayer->isCrouching = playerData->GetIsCrouching();
                            oldPlayer->currentSpread = playerData->GetCurrentSpread();
                            oldPlayer->speedM = playerData->GetSpeedM();
                            oldPlayer->isGhost = playerData->GetIsGhost();
                        }

                        newPlayers[oldKey] = oldPlayer;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    auto cachedPlayer = std::make_shared<CachedPlayer>();
                    cachedPlayer->gamePlayer = gamePlayer;
                    cachedPlayer->playerData = playerData;
                    cachedPlayer->teamId = gamePlayer->GetTeamID();
                    cachedPlayer->health = gamePlayer->GetCurrentHealth();
                    cachedPlayer->headPosition = gamePlayer->GetHeadPos();
                    cachedPlayer->isLocalPlayer = gamePlayer->IsLocalPlayer();
                    cachedPlayer->isValid = true;
                    cachedPlayer->lastUpdateTime = currentTime;
                    cachedPlayer->actorNumber = i;

                    if (playerData) {
                        cachedPlayer->isReloading = playerData->GetIsReloading();
                        cachedPlayer->reloadProgress = playerData->GetReloadingProgress();
                        cachedPlayer->totalAmmo = playerData->GetTotalAmmo();
                        cachedPlayer->bulletsLoaded = playerData->GetBulletsLoaded();
                        cachedPlayer->isGrounded = playerData->GetIsGrounded();
                        cachedPlayer->isCrouching = playerData->GetIsCrouching();
                        cachedPlayer->currentSpread = playerData->GetCurrentSpread();
                        cachedPlayer->speedM = playerData->GetSpeedM();
                        cachedPlayer->isGhost = playerData->GetIsGhost();
                        cachedPlayer->name = playerData->GetPlayerName();
                    }

                    if (cachedPlayer->name.empty()) {
                        cachedPlayer->name = cachedPlayer->isLocalPlayer ? "You" : "Player_" + std::to_string(i);
                    }

                    newPlayers[i] = cachedPlayer;

                    if (cachedPlayer->isLocalPlayer) {
                        localPlayer = cachedPlayer;
                    }
                }

            }
            catch (...) {
            }
        }

        players = std::move(newPlayers);

    }
    catch (...) {
    }
}

std::vector<std::shared_ptr<CachedPlayer>> PlayerCache::GetPlayers() {
    std::lock_guard<std::mutex> lock(cacheMutex);
    std::vector<std::shared_ptr<CachedPlayer>> result;

    for (auto& [actorNumber, player] : players) {
        if (player->isValid) {
            result.push_back(player);
        }
    }

    return result;
}

std::shared_ptr<CachedPlayer> PlayerCache::GetPlayerByActorNumber(int32_t actorNumber) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    auto it = players.find(actorNumber);
    return (it != players.end() && it->second->isValid) ? it->second : nullptr;
}

std::shared_ptr<CachedPlayer> PlayerCache::GetLocalPlayer() {
    std::lock_guard<std::mutex> lock(cacheMutex);
    return localPlayer;
}

std::vector<std::shared_ptr<CachedPlayer>> PlayerCache::GetEnemyPlayers() {
    auto local = GetLocalPlayer();
    if (!local) return {};

    std::vector<std::shared_ptr<CachedPlayer>> enemies;
    auto allPlayers = GetPlayers();

    for (auto& player : allPlayers) {
        if (player->actorNumber != local->actorNumber && player->teamId != local->teamId) {
            enemies.push_back(player);
        }
    }

    return enemies;
}

std::vector<std::shared_ptr<CachedPlayer>> PlayerCache::GetTeammates() {
    auto local = GetLocalPlayer();
    if (!local) return {};

    std::vector<std::shared_ptr<CachedPlayer>> teammates;
    auto allPlayers = GetPlayers();

    for (auto& player : allPlayers) {
        if (player->actorNumber != local->actorNumber && player->teamId == local->teamId) {
            teammates.push_back(player);
        }
    }

    return teammates;
}

void PlayerCache::ClearCache() {
    std::lock_guard<std::mutex> lock(cacheMutex);
    players.clear();
    localPlayer.reset();
}