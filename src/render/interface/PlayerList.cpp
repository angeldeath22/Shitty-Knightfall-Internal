#include "PlayerList.hpp"


void PlayerList::Render() {
    if (!ImGui::CollapsingHeader("Player List", ImGuiTreeNodeFlags_DefaultOpen))
        return;

    auto& cache = PlayerCache::GetInstance();
    auto players = cache.GetPlayers();
    auto localPlayer = cache.GetLocalPlayer();

    if (players.empty()) {
        ImGui::Text("No players found");
        return;
    }

    ImGui::Text("Players: %d", players.size());
    ImGui::Separator();

    for (auto& player : players) {
        if (!player->isValid) continue;
        RenderPlayer(player);
    }
}

void PlayerList::RenderPlayer(std::shared_ptr<CachedPlayer> player) {
    if (!player || !player->isValid) return;

    auto localPlayer = PlayerCache::GetInstance().GetLocalPlayer();

    std::string header = GetPlayerPrefix(player) + player->name;


    if (player->health < 100.0f) {
        header += " [" + std::to_string(static_cast<int>(player->health)) + "HP]";
    }

    ImGui::PushStyleColor(ImGuiCol_Header, GetPlayerColor(player));

    if (ImGui::CollapsingHeader(header.c_str())) {
        ImGui::PopStyleColor();

        ImGui::Indent();


        ImGui::Text("Actor: %d", player->actorNumber);
        ImGui::Text("Team: %llu", player->teamId);
        ImGui::Text("Health: %.1f", player->health);

        if (!player->userId.empty()) {
            ImGui::Text("ID: %s", player->userId.c_str());
        }

        ImGui::Text("Position: (%.1f, %.1f, %.1f)",
            player->headPosition.x,
            player->headPosition.y,
            player->headPosition.z);


        if (localPlayer && localPlayer->isValid) {
            float distance = Vector3::Distance(localPlayer->headPosition, player->headPosition);
            ImGui::Text("Distance: %.1fm", distance);
        }

        ImGui::Separator();
        ImGui::Text("Status:");
        ImGui::BulletText("%s", player->isLocalPlayer ? "Local Player" : "Remote Player");
        ImGui::BulletText("%s", player->isMasterClient ? "Master Client" : "Normal Client");

        if (localPlayer) {
            ImGui::BulletText("%s", player->teamId == localPlayer->teamId ? "Teammate" : "Enemy");
        }

        ImGui::Unindent();
    }
    else {
        ImGui::PopStyleColor();
    }
}

const char* PlayerList::GetPlayerPrefix(std::shared_ptr<CachedPlayer> player) {
    if (player->isLocalPlayer) return "[YOU] ";
    if (player->isMasterClient) return "[M] ";
    if (player->teamId != PlayerCache::GetInstance().GetLocalPlayer()->teamId) return "[E] ";
    return "[T] ";
}

ImVec4 PlayerList::GetPlayerColor(std::shared_ptr<CachedPlayer> player) {
    auto localPlayer = PlayerCache::GetInstance().GetLocalPlayer();

    if (player->isLocalPlayer)
        return ImVec4(0.0f, 0.5f, 1.0f, 0.3f); // Blue

    if (player->isMasterClient)
        return ImVec4(1.0f, 0.5f, 0.0f, 0.3f); // Orange

    if (player->teamId == localPlayer->teamId)
        return ImVec4(0.0f, 0.8f, 0.0f, 0.3f); // Green

    return ImVec4(0.8f, 0.0f, 0.0f, 0.3f); // Red
}

void PlayerList::RenderPlayerActions(std::shared_ptr<CachedPlayer> player) {
    auto localPlayer = PlayerCache::GetInstance().GetLocalPlayer();

    ImGui::Text("Actions:");

    
}