#define NOMINMAX
#include "ESP.hpp"
#include "../sdk/game/PlayerCache.hpp"
#include "Toggles.hpp"
#include <iostream>

class UnityCamera {
public:
    static void* GetMainCamera() {
        auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
        auto getMainFunc = reinterpret_cast<void* (__stdcall*)(void*)>(base + 0xD7B0A0);
        return getMainFunc(nullptr);
    }

    static Vector3 WorldToScreenPoint(void* camera, const Vector3& worldPos) {
        if (!camera) return Vector3(0, 0, -1);
        auto base = reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
        auto worldToScreenFunc = reinterpret_cast<Vector3(__stdcall*)(void*, Vector3, void*)>(base + 0xD7AAC0);
        return worldToScreenFunc(camera, worldPos, nullptr);
    }
};

void ESP::Render() {
    if (!Toggles::ESPEnabled) return;

    auto& cache = PlayerCache::GetInstance();
    auto players = cache.GetPlayers();
    auto localPlayer = cache.GetLocalPlayer();

    if (!localPlayer) return;

    void* mainCamera = UnityCamera::GetMainCamera();
    if (!mainCamera) return;

    for (auto player : players) {
        if (!player || !player->isValid) continue;

        if (player->isLocalPlayer && !Toggles::ESPLocalPlayer) continue;
        if (!player->isLocalPlayer && player->teamId == localPlayer->teamId && !Toggles::ESPTeammates) continue;
        if (!player->isLocalPlayer && player->teamId != localPlayer->teamId && !Toggles::ESPEnemies) continue;

        float distance = Vector3::Distance(localPlayer->headPosition, player->headPosition);
        if (distance > config.maxDistance) continue;

        RenderPlayerESP(player, mainCamera);
    }
}

void ESP::Update() {
    static uint64_t lastBoneClean = 0;
    if (GetTickCount64() - lastBoneClean > 10000) {
        g_playerBones.clear();
        lastBoneClean = GetTickCount64();
    }
}

void ESP::RenderPlayerESP(std::shared_ptr<CachedPlayer> player, void* camera) {
    auto localPlayer = PlayerCache::GetInstance().GetLocalPlayer();
    if (!localPlayer) return;

    if (Toggles::ESPBoxes) {
        if (config.threeDBox) {
            Draw3DBoxESP(player, camera);
        }
        else {
            DrawBoxESP(player, camera);
        }
    }
    if (Toggles::ESPSnaplines && config.showSnaplines) DrawSnapline(player, camera);
    if (Toggles::ESPHealthBars && config.showHealthBar) DrawHealthBar(player, camera);
    if (Toggles::ESPNames && config.showNameTags) DrawNameTag(player, camera);
    if (Toggles::ESPDistance && config.showDistance) DrawDistance(player, camera);
    if (Toggles::ESPSkeletons && config.showSkeletons) DrawSkeleton(player, camera);
    if (config.showPlayerInfo) DrawPlayerInfo(player, camera);
}

void ESP::DrawBoxESP(std::shared_ptr<CachedPlayer> player, void* camera) {
    Vector3 headPos = player->headPosition;
    Vector3 feetPos = Vector3(headPos.x, headPos.y - 2.0f, headPos.z);

    Vector3 leftShoulder = Vector3(headPos.x - 0.4f, headPos.y - 0.3f, headPos.z);
    Vector3 rightShoulder = Vector3(headPos.x + 0.4f, headPos.y - 0.3f, headPos.z);

    ImVec2 headScreen, feetScreen, leftShoulderScreen, rightShoulderScreen;

    if (WorldToScreen(headPos, headScreen, camera) &&
        WorldToScreen(feetPos, feetScreen, camera)) {

        float height = std::abs(headScreen.y - feetScreen.y);
        float width = height * 0.5f;

        if (WorldToScreen(leftShoulder, leftShoulderScreen, camera) &&
            WorldToScreen(rightShoulder, rightShoulderScreen, camera)) {
            width = std::abs(rightShoulderScreen.x - leftShoulderScreen.x);
            width = std::max(width, height * 0.4f);
            width = std::min(width, height * 0.8f);
        }

        ImVec2 topLeft = ImVec2(headScreen.x - width / 2, feetScreen.y);
        ImVec2 bottomRight = ImVec2(headScreen.x + width / 2, headScreen.y);

        ImColor boxColor = GetPlayerColor(player);

        ImGui::GetBackgroundDrawList()->AddRect(topLeft, bottomRight, boxColor, 3.0f, 0, config.boxThickness);

        if (config.filledBoxes) {
            ImColor fillColor = boxColor;
            fillColor.Value.w = config.boxAlpha;
            ImGui::GetBackgroundDrawList()->AddRectFilled(topLeft, bottomRight, fillColor, 3.0f);
        }

        if (config.cornerBox && config.boxThickness > 1.0f) {
            DrawCornerBox(topLeft, bottomRight, boxColor, config.boxThickness);
        }
    }
}

void ESP::Draw3DBoxESP(std::shared_ptr<CachedPlayer> player, void* camera) {
    Vector3 headPos = player->headPosition;
    Vector3 feetPos = Vector3(headPos.x, headPos.y - 1.8f, headPos.z);

    std::vector<Vector3> boxPoints = {
        Vector3(headPos.x - 0.3f, feetPos.y, headPos.z - 0.2f),
        Vector3(headPos.x + 0.3f, feetPos.y, headPos.z - 0.2f),
        Vector3(headPos.x + 0.3f, feetPos.y, headPos.z + 0.2f),
        Vector3(headPos.x - 0.3f, feetPos.y, headPos.z + 0.2f),
        Vector3(headPos.x - 0.3f, headPos.y, headPos.z - 0.2f),
        Vector3(headPos.x + 0.3f, headPos.y, headPos.z - 0.2f),
        Vector3(headPos.x + 0.3f, headPos.y, headPos.z + 0.2f),
        Vector3(headPos.x - 0.3f, headPos.y, headPos.z + 0.2f)
    };

    std::vector<ImVec2> screenPoints;
    for (const auto& point : boxPoints) {
        ImVec2 screenPoint;
        if (WorldToScreen(point, screenPoint, camera)) {
            screenPoints.push_back(screenPoint);
        }
    }

    if (screenPoints.size() == 8) {
        ImColor boxColor = GetPlayerColor(player);

        for (int i = 0; i < 4; i++) {
            ImGui::GetBackgroundDrawList()->AddLine(screenPoints[i], screenPoints[(i + 1) % 4], boxColor, config.boxThickness);
        }

        for (int i = 4; i < 8; i++) {
            ImGui::GetBackgroundDrawList()->AddLine(screenPoints[i], screenPoints[4 + (i - 4 + 1) % 4], boxColor, config.boxThickness);
        }

        for (int i = 0; i < 4; i++) {
            ImGui::GetBackgroundDrawList()->AddLine(screenPoints[i], screenPoints[i + 4], boxColor, config.boxThickness);
        }
    }
}

void ESP::DrawCornerBox(const ImVec2& topLeft, const ImVec2& bottomRight, ImColor color, float thickness) {
    float width = bottomRight.x - topLeft.x;
    float height = bottomRight.y - topLeft.y;
    float cornerLength = std::min(width, height) * 0.2f;

    ImGui::GetBackgroundDrawList()->AddLine(topLeft, ImVec2(topLeft.x + cornerLength, topLeft.y), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + cornerLength), color, thickness);

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottomRight.x, topLeft.y), ImVec2(bottomRight.x - cornerLength, topLeft.y), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottomRight.x, topLeft.y), ImVec2(bottomRight.x, topLeft.y + cornerLength), color, thickness);

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(topLeft.x, bottomRight.y), ImVec2(topLeft.x + cornerLength, bottomRight.y), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(topLeft.x, bottomRight.y), ImVec2(topLeft.x, bottomRight.y - cornerLength), color, thickness);

    ImGui::GetBackgroundDrawList()->AddLine(bottomRight, ImVec2(bottomRight.x - cornerLength, bottomRight.y), color, thickness);
    ImGui::GetBackgroundDrawList()->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - cornerLength), color, thickness);
}

void ESP::DrawSnapline(std::shared_ptr<CachedPlayer> player, void* camera) {
    ImVec2 playerScreen;
    Vector3 feetPos = Vector3(player->headPosition.x, player->headPosition.y - 1.8f, player->headPosition.z);

    if (WorldToScreen(feetPos, playerScreen, camera)) {
        ImVec2 screenBottom = ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y);
        ImColor lineColor = GetPlayerColor(player);
        ImGui::GetBackgroundDrawList()->AddLine(screenBottom, playerScreen, lineColor, config.snaplineThickness);
    }
}

void ESP::DrawHealthBar(std::shared_ptr<CachedPlayer> player, void* camera) {
    ImVec2 headScreen;

    if (WorldToScreen(player->headPosition, headScreen, camera)) {
        float healthPercent = player->health / 100.0f;
        float barWidth = 30.0f;
        float barHeight = 4.0f;
        float barX = headScreen.x - barWidth / 2;
        float barY = headScreen.y - 75.0f;

        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(barX, barY), ImVec2(barX + barWidth, barY + barHeight), ImColor(50, 50, 50, 200));

        ImColor healthColor;
        if (healthPercent > 0.7f) healthColor = ImColor(50, 255, 50, 255);
        else if (healthPercent > 0.3f) healthColor = ImColor(255, 255, 50, 255);
        else healthColor = ImColor(255, 50, 50, 255);

        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(barX, barY), ImVec2(barX + (barWidth * healthPercent), barY + barHeight), healthColor);

        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(barX, barY), ImVec2(barX + barWidth, barY + barHeight), ImColor(255, 255, 255, 255), 0, 0, 1.0f);
    }
}

void ESP::DrawNameTag(std::shared_ptr<CachedPlayer> player, void* camera) {
    ImVec2 headScreen;

    if (WorldToScreen(player->headPosition, headScreen, camera)) {
        ImColor textColor = GetPlayerColor(player);

        std::string displayName = player->name;

        if (Toggles::ESPDistance) {
            float distance = Vector3::Distance(PlayerCache::GetInstance().GetLocalPlayer()->headPosition, player->headPosition);
            displayName += " [" + std::to_string(static_cast<int>(distance)) + "m]";
        }

        ImVec2 textSize = ImGui::CalcTextSize(displayName.c_str());
        ImVec2 textPos = ImVec2(headScreen.x - textSize.x / 2, headScreen.y - 90.0f);

        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(textPos.x - 2, textPos.y - 2), ImVec2(textPos.x + textSize.x + 2, textPos.y + textSize.y + 2), ImColor(0, 0, 0, 150));
        ImGui::GetBackgroundDrawList()->AddText(textPos, textColor, displayName.c_str());
    }
}

void ESP::DrawPlayerInfo(std::shared_ptr<CachedPlayer> player, void* camera) {
    ImVec2 headScreen;

    if (WorldToScreen(player->headPosition, headScreen, camera)) {
        ImColor textColor = GetPlayerColor(player);
        std::vector<std::string> infoLines;

        if (config.showAmmo && player->bulletsLoaded > 0) {
            std::string ammoText = "Ammo: " + std::to_string(player->bulletsLoaded);
            if (player->totalAmmo > 0) {
                ammoText += "/" + std::to_string(player->totalAmmo);
            }
            infoLines.push_back(ammoText);
        }

        if (config.showReload && player->isReloading) {
            infoLines.push_back("Reloading: " + std::to_string(static_cast<int>(player->reloadProgress * 100)) + "%");
        }

        if (config.showStatus) {
            if (player->isGhost) {
                infoLines.push_back("GHOST");
            }
            if (player->isCrouching) {
                infoLines.push_back("CROUCHING");
            }
            if (player->currentBombs > 0) {
                infoLines.push_back("Bombs: " + std::to_string(player->currentBombs));
            }
            if (player->currentBandage > 0) {
                infoLines.push_back("Bandages: " + std::to_string(player->currentBandage));
            }
        }

        if (config.showWeapon && player->currentWeaponID > 0) {
            std::string weaponName = GetWeaponName(player->currentWeaponID);
            if (!weaponName.empty()) {
                infoLines.push_back(weaponName);
            }
        }

        float currentY = headScreen.y - 75.0f;

        for (const auto& line : infoLines) {
            ImVec2 lineSize = ImGui::CalcTextSize(line.c_str());
            ImVec2 linePos = ImVec2(headScreen.x - lineSize.x / 2, currentY);

            ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(linePos.x - 2, linePos.y - 2), ImVec2(linePos.x + lineSize.x + 2, linePos.y + lineSize.y + 2), ImColor(0, 0, 0, 150));
            ImGui::GetBackgroundDrawList()->AddText(linePos, textColor, line.c_str());

            currentY += lineSize.y + 2;
        }
    }
}

void ESP::DrawDistance(std::shared_ptr<CachedPlayer> player, void* camera) {
    ImVec2 headScreen;

    if (WorldToScreen(player->headPosition, headScreen, camera)) {
        float distance = Vector3::Distance(PlayerCache::GetInstance().GetLocalPlayer()->headPosition, player->headPosition);

        std::string distanceText = std::to_string(static_cast<int>(distance)) + "m";
        ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());
        ImVec2 textPos = ImVec2(headScreen.x - textSize.x / 2, headScreen.y - 75.0f);

        ImColor textColor = GetPlayerColor(player);

        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(textPos.x - 2, textPos.y - 2), ImVec2(textPos.x + textSize.x + 2, textPos.y + textSize.y + 2), ImColor(0, 0, 0, 150));
        ImGui::GetBackgroundDrawList()->AddText(textPos, textColor, distanceText.c_str());
    }
}

void ESP::DrawSkeleton(std::shared_ptr<CachedPlayer> player, void* camera) {
    auto& bones = g_playerBones[player->gamePlayer->GetInstance()];

    if (bones.empty()) {
        EstimateBonePositions(player, bones);
    }

    ImColor skeletonColor = GetPlayerColor(player);

    for (size_t i = 0; i < bones.size(); i++) {
        for (size_t j = i + 1; j < bones.size(); j++) {
            if (IsBoneConnected(bones[i].boneId, bones[j].boneId)) {
                ImVec2 screen1, screen2;
                if (WorldToScreen(bones[i].position, screen1, camera) &&
                    WorldToScreen(bones[j].position, screen2, camera)) {
                    ImGui::GetBackgroundDrawList()->AddLine(screen1, screen2, skeletonColor, config.skeletonThickness);
                }
            }
        }
    }
}

void ESP::EstimateBonePositions(std::shared_ptr<CachedPlayer> player, std::vector<BoneInfo>& bones) {
    Vector3 headPos = player->headPosition;

    bones = {
        {headPos, UnityEngine::HumanBodyBones::Head},
        {Vector3(headPos.x, headPos.y - 0.2f, headPos.z), UnityEngine::HumanBodyBones::Neck},
        {Vector3(headPos.x, headPos.y - 0.5f, headPos.z), UnityEngine::HumanBodyBones::Chest},
        {Vector3(headPos.x, headPos.y - 0.8f, headPos.z), UnityEngine::HumanBodyBones::Spine},
        {Vector3(headPos.x, headPos.y - 1.2f, headPos.z), UnityEngine::HumanBodyBones::Hips},
        {Vector3(headPos.x - 0.3f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::LeftShoulder},
        {Vector3(headPos.x - 0.5f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::LeftUpperArm},
        {Vector3(headPos.x - 0.7f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::LeftLowerArm},
        {Vector3(headPos.x - 0.8f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::LeftHand},
        {Vector3(headPos.x + 0.3f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::RightShoulder},
        {Vector3(headPos.x + 0.5f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::RightUpperArm},
        {Vector3(headPos.x + 0.7f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::RightLowerArm},
        {Vector3(headPos.x + 0.8f, headPos.y - 0.3f, headPos.z), UnityEngine::HumanBodyBones::RightHand},
        {Vector3(headPos.x - 0.1f, headPos.y - 1.2f, headPos.z), UnityEngine::HumanBodyBones::LeftUpperLeg}, //doesnt work wrote this fucking hammered man
        {Vector3(headPos.x - 0.1f, headPos.y - 1.6f, headPos.z), UnityEngine::HumanBodyBones::LeftLowerLeg},
        {Vector3(headPos.x - 0.1f, headPos.y - 1.8f, headPos.z), UnityEngine::HumanBodyBones::LeftFoot},
        {Vector3(headPos.x + 0.1f, headPos.y - 1.2f, headPos.z), UnityEngine::HumanBodyBones::RightUpperLeg},
        {Vector3(headPos.x + 0.1f, headPos.y - 1.6f, headPos.z), UnityEngine::HumanBodyBones::RightLowerLeg},
        {Vector3(headPos.x + 0.1f, headPos.y - 1.8f, headPos.z), UnityEngine::HumanBodyBones::RightFoot}
    };
}

bool ESP::IsBoneConnected(UnityEngine::HumanBodyBones bone1, UnityEngine::HumanBodyBones bone2) {
    static std::vector<std::pair<UnityEngine::HumanBodyBones, UnityEngine::HumanBodyBones>> connections = {
        {UnityEngine::HumanBodyBones::Head, UnityEngine::HumanBodyBones::Neck},
        {UnityEngine::HumanBodyBones::Neck, UnityEngine::HumanBodyBones::Chest},
        {UnityEngine::HumanBodyBones::Chest, UnityEngine::HumanBodyBones::Spine},
        {UnityEngine::HumanBodyBones::Spine, UnityEngine::HumanBodyBones::Hips},
        {UnityEngine::HumanBodyBones::Chest, UnityEngine::HumanBodyBones::LeftShoulder},
        {UnityEngine::HumanBodyBones::LeftShoulder, UnityEngine::HumanBodyBones::LeftUpperArm},
        {UnityEngine::HumanBodyBones::LeftUpperArm, UnityEngine::HumanBodyBones::LeftLowerArm},
        {UnityEngine::HumanBodyBones::LeftLowerArm, UnityEngine::HumanBodyBones::LeftHand},
        {UnityEngine::HumanBodyBones::Chest, UnityEngine::HumanBodyBones::RightShoulder},
        {UnityEngine::HumanBodyBones::RightShoulder, UnityEngine::HumanBodyBones::RightUpperArm},
        {UnityEngine::HumanBodyBones::RightUpperArm, UnityEngine::HumanBodyBones::RightLowerArm},
        {UnityEngine::HumanBodyBones::RightLowerArm, UnityEngine::HumanBodyBones::RightHand},
        {UnityEngine::HumanBodyBones::Hips, UnityEngine::HumanBodyBones::LeftUpperLeg},
        {UnityEngine::HumanBodyBones::LeftUpperLeg, UnityEngine::HumanBodyBones::LeftLowerLeg},
        {UnityEngine::HumanBodyBones::LeftLowerLeg, UnityEngine::HumanBodyBones::LeftFoot},
        {UnityEngine::HumanBodyBones::Hips, UnityEngine::HumanBodyBones::RightUpperLeg},
        {UnityEngine::HumanBodyBones::RightUpperLeg, UnityEngine::HumanBodyBones::RightLowerLeg},
        {UnityEngine::HumanBodyBones::RightLowerLeg, UnityEngine::HumanBodyBones::RightFoot}
    };

    for (auto& connection : connections) {
        if ((connection.first == bone1 && connection.second == bone2) ||
            (connection.first == bone2 && connection.second == bone1)) {
            return true;
        }
    }
    return false;
}

ImColor ESP::GetPlayerColor(std::shared_ptr<CachedPlayer> player) {
    auto localPlayer = PlayerCache::GetInstance().GetLocalPlayer();
    if (!localPlayer) return ESPColors::Enemy;

    if (player->isLocalPlayer) return ESPColors::LocalPlayer;
    if (player->teamId == localPlayer->teamId) return ESPColors::Teammate;
    return ESPColors::Enemy;
}

std::string ESP::GetWeaponName(int weaponId) { // no mi amigo

    return "Weapon " + std::to_string(weaponId); //place holder until i actually do something
}

bool ESP::WorldToScreen(const Vector3& worldPos, ImVec2& screenPos, void* camera) {
    if (!camera) {
        camera = UnityCamera::GetMainCamera();
        if (!camera) return false;
    }

    Vector3 screenPoint = UnityCamera::WorldToScreenPoint(camera, worldPos);
    if (screenPoint.z < 0.1f) return false;

    screenPos.x = screenPoint.x;
    screenPos.y = ImGui::GetIO().DisplaySize.y - screenPoint.y;

    return (screenPos.x >= 0 && screenPos.x <= ImGui::GetIO().DisplaySize.x &&
        screenPos.y >= 0 && screenPos.y <= ImGui::GetIO().DisplaySize.y);
}

bool ESP::WorldToScreen(const Vector3& worldPos, ImVec2& screenPos) {
    return WorldToScreen(worldPos, screenPos, nullptr);
}