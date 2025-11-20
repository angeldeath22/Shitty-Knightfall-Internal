#pragma once
#include <imgui/imgui.h>
#include <unordered_map>
#include <vector>
#include "../../sdk/game/PlayerCache.hpp"
#include "Toggles.hpp"
#include <math.hpp>
#include "../sdk/game/BonesType.hpp"

class ESP {
public:
    static void Render();
    static void Update();

    struct ESPConfig {
        float maxDistance = 250.0f;
        float boxThickness = 2.0f;
        float snaplineThickness = 1.0f;
        bool filledBoxes = false;
        float boxAlpha = 0.3f;
        float skeletonThickness = 1.0f;
        bool showAmmo = true;
        bool showReload = true;
        bool showStatus = true;
        bool showWeapon = true;
        bool cornerBox = true;
        bool threeDBox = false;
        bool showHealthBar = true;
        bool showNameTags = true;
        bool showDistance = true;
        bool showSnaplines = true;
        bool showSkeletons = true;
        bool showPlayerInfo = true;
    };

    static inline ESPConfig config;

private:
    struct BoneInfo {
        Vector3 position;
        UnityEngine::HumanBodyBones boneId;
    };

    static void RenderPlayerESP(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawBoxESP(std::shared_ptr<CachedPlayer> player, void* camera);
    static void Draw3DBoxESP(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawCornerBox(const ImVec2& topLeft, const ImVec2& bottomRight, ImColor color, float thickness);
    static void DrawSnapline(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawHealthBar(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawNameTag(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawDistance(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawSkeleton(std::shared_ptr<CachedPlayer> player, void* camera);
    static void DrawPlayerInfo(std::shared_ptr<CachedPlayer> player, void* camera);
    static void EstimateBonePositions(std::shared_ptr<CachedPlayer> player, std::vector<BoneInfo>& bones);
    static bool IsBoneConnected(UnityEngine::HumanBodyBones bone1, UnityEngine::HumanBodyBones bone2);
    static ImColor GetPlayerColor(std::shared_ptr<CachedPlayer> player);
    static std::string GetWeaponName(int weaponId);
    static bool WorldToScreen(const Vector3& worldPos, ImVec2& screenPos, void* camera);
    static bool WorldToScreen(const Vector3& worldPos, ImVec2& screenPos);

    static inline std::unordered_map<void*, std::vector<BoneInfo>> g_playerBones;
};