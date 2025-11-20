#pragma once
#include <imgui/imgui.h>
#include <memory>
#include "../../sdk/game/PlayerCache.hpp"

class PlayerList {
public:
    static void Render();

private:
    static void RenderPlayer(std::shared_ptr<CachedPlayer> player);
    static const char* GetPlayerPrefix(std::shared_ptr<CachedPlayer> player);
    static ImVec4 GetPlayerColor(std::shared_ptr<CachedPlayer> player);
    static void RenderPlayerActions(std::shared_ptr<CachedPlayer> player);
};