#pragma once

class Menu {
public:
    static void Render();
private:
    static void RenderMainWindow();
    static void RenderMainTab();
    static void RenderPlayersTab();
    static void RenderWeaponTab();
    static void RenderinstantiateTab();
    static void RenderPhotonTab();
    static void RenderMiscTab();
    static void RenderSettingsTab();
};