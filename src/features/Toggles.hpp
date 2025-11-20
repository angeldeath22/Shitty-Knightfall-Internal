#pragma once
#include <imgui/imgui.h>
namespace Toggles {

    inline bool LocalGodMode = false;
    inline bool SpeedHack = false;
    inline bool InfiniteAmmo = false;
    inline bool NoRecoil = false;
    inline bool NoSpread = false;


    inline bool ESP = false;
    inline bool ShowTeammates = false;
    inline bool ShowEnemies = true;
    inline bool ShowNameTags = true; //one of these isnt used, uhm idk wich one i will come back later and fix ts
    inline bool ShowHealthBars = true;
    inline bool ShowDistance = true;


    inline bool Aimbot = false;
    inline bool TriggerBot = false;
    inline bool SilentAim = false;
    inline bool AutoReload = false;


    inline bool FlyHack = false;
    inline bool NoClip = false;
    inline bool SuperJump = false;

    inline bool NameSpoof = false;
    inline bool TeamChanger = false;
    inline bool InstantRespawn = false;


    inline bool ESPEnabled = true;
    inline bool ESPBoxes = true;
    inline bool ESPSnaplines = true;
    inline bool ESPHealthBars = true;
    inline bool ESPNames = true;
    inline bool ESPDistance = true;
    inline bool ESPSkeletons = false;
    inline bool ESPTeammates = true;
    inline bool ESPEnemies = true;
    inline bool ESPLocalPlayer = false;
}

namespace ESPColors {
    inline ImColor Enemy = ImColor(255, 50, 50, 255);
    inline ImColor Teammate = ImColor(50, 255, 50, 255);
    inline ImColor LocalPlayer = ImColor(50, 150, 255, 255);
    inline ImColor Friendly = ImColor(100, 200, 255, 255);
}