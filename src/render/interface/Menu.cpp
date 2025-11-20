#include "Menu.hpp"
#include "imgui/imgui.h"
#include "PlayerList.hpp"
#include "../../features/Toggles.hpp"
#include "../../features/ESP.hpp"
#include "../../utils/CMD/Logger.hpp"
void Menu::Render() {
    RenderMainWindow();
}



void Menu::RenderMainWindow() {
    ImGui::SetNextWindowSize(ImVec2(600, 430), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(120, 120), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize;

    if (ImGui::Begin("Hentai-Hook", nullptr, flags)) {
        if (ImGui::BeginTabBar("MainTabs", ImGuiTabBarFlags_NoTooltip)) {

            if (ImGui::BeginTabItem("Main")) { RenderMainTab(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Players")) { RenderPlayersTab(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Weapon")) { RenderWeaponTab(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Instantiate")) { RenderinstantiateTab();   ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Photon")) { RenderPhotonTab();  ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Misc")) { RenderMiscTab();   ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Settings")) { RenderSettingsTab(); ImGui::EndTabItem(); }

            ImGui::EndTabBar();
        }
    }

    ImGui::End();
}
void Menu::RenderMainTab() {


    float w = ImGui::GetWindowWidth();
    ImGui::SetCursorPosX((w - 150) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() + -100);

    ImGui::Text("THIS TAB IS NOT DONE YET");


}




void Menu::RenderPlayersTab() 
{ 
    if (ImGui::CollapsingHeader("ESP"))
    {
        ImGui::Indent(12);
        ImGui::Checkbox("ESP Enabled", &Toggles::ESPEnabled);

        ImGui::Separator();
        ImGui::Checkbox("Box ESP", &Toggles::ESPBoxes);
        ImGui::Checkbox("Snaplines", &Toggles::ESPSnaplines);
        ImGui::Checkbox("Health Bars", &Toggles::ESPHealthBars);
        ImGui::Checkbox("Name Tags", &Toggles::ESPNames);
        ImGui::Checkbox("Distance", &Toggles::ESPDistance);
        ImGui::Checkbox("Skeletons", &Toggles::ESPSkeletons);

        ImGui::Separator();
        ImGui::Checkbox("Show Teammates", &Toggles::ESPTeammates);
        ImGui::Checkbox("Show Enemies", &Toggles::ESPEnemies);
        ImGui::Checkbox("Show Local Player", &Toggles::ESPLocalPlayer);

        ImGui::Separator();
        ImGui::Checkbox("Filled Boxes", &ESP::config.filledBoxes);
        if (ESP::config.filledBoxes) {
            ImGui::SliderFloat("Box Alpha", &ESP::config.boxAlpha, 0.1f, 1.0f);
        }
        ImGui::SliderFloat("Box Thickness", &ESP::config.boxThickness, 0.5f, 5.0f);
        ImGui::Checkbox("Corner Box", &ESP::config.cornerBox);
        ImGui::Checkbox("3D Box", &ESP::config.threeDBox);

        ImGui::Separator();
        ImGui::SliderFloat("Max Distance", &ESP::config.maxDistance, 10.0f, 500.0f, "%.1fm");
        ImGui::SliderFloat("Snapline Thickness", &ESP::config.snaplineThickness, 0.5f, 3.0f);
        ImGui::SliderFloat("Skeleton Thickness", &ESP::config.skeletonThickness, 0.5f, 3.0f);

        ImGui::Separator();
        ImGui::Checkbox("Show Ammo", &ESP::config.showAmmo);
        ImGui::Checkbox("Show Reload", &ESP::config.showReload);
        ImGui::Checkbox("Show Status", &ESP::config.showStatus);
        ImGui::Checkbox("Show Weapon", &ESP::config.showWeapon);
        ImGui::Checkbox("Show Health Bar", &ESP::config.showHealthBar);
        ImGui::Checkbox("Show Name Tags", &ESP::config.showNameTags);
        ImGui::Checkbox("Show Distance", &ESP::config.showDistance);
        ImGui::Checkbox("Show Snaplines", &ESP::config.showSnaplines);
        ImGui::Checkbox("Show Skeletons", &ESP::config.showSkeletons);
        ImGui::Checkbox("Show Player Info", &ESP::config.showPlayerInfo);

        ImGui::Separator();
        ImGui::ColorEdit4("Enemy Color", (float*)&ESPColors::Enemy);
        ImGui::ColorEdit4("Teammate Color", (float*)&ESPColors::Teammate);
        ImGui::ColorEdit4("Local Player Color", (float*)&ESPColors::LocalPlayer);
        ImGui::Unindent(12);
        ImGui::Spacing();
    }

    PlayerList::Render(); 

}

void Menu::RenderWeaponTab() {
    float a = ImGui::GetWindowWidth();
    ImGui::SetCursorPosX((a - 150) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() + -100);

    ImGui::Text("THIS TAB IS NOT DONE YET");


}

void Menu::RenderinstantiateTab() {
    float m = ImGui::GetWindowWidth();
    ImGui::SetCursorPosX((m - 150) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() + -100);

    ImGui::Text("THIS TAB IS NOT DONE YET");

}

void Menu::RenderPhotonTab() {
    float c = ImGui::GetWindowWidth();
    ImGui::SetCursorPosX((c - 150) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() + -100);

    ImGui::Text("THIS TAB IS NOT DONE YET");


}

void Menu::RenderMiscTab() {
    float e = ImGui::GetWindowWidth();
    ImGui::SetCursorPosX((e - 150) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() + -100);

    ImGui::Text("THIS TAB IS NOT DONE YET");


}

void Menu::RenderSettingsTab() {
    float g = ImGui::GetWindowWidth();
    ImGui::SetCursorPosX((g - 150) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() + -100);

    ImGui::Text("THIS TAB IS NOT DONE YET");

}