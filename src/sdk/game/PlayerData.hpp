#pragma once
#include <string>
#include "il2cpp-api-types.h"
#include <math.hpp>
#include "../funcs.hpp"

class PlayerData {
public:
    PlayerData(void* instance) : instance(instance) {}

    bool IsValid() const {
        return instance != nullptr && IsValidPointer(instance);
    }

    std::string GetPlayerName() {
        if (!IsValid()) return "";
        auto str = SafeGetField<Il2CppString*>(instance, 0x10, nullptr);
        return str && IsValidString(str) ? Il2CppStringToStdString(str) : "";
    }

    bool GetNeedHorse() { return IsValid() ? SafeGetField<bool>(instance, 0x18, false) : false; }
    float GetDontDoActionsFor() { return IsValid() ? SafeGetField<float>(instance, 0x1C, 0.0f) : 0.0f; }
    float GetCurrentSpread() { return IsValid() ? SafeGetField<float>(instance, 0x20, 0.0f) : 0.0f; }
    float GetSinceAbilityUse() { return IsValid() ? SafeGetField<float>(instance, 0x24, 0.0f) : 0.0f; }
    bool GetIsReloading() { return IsValid() ? SafeGetField<bool>(instance, 0x28, false) : false; }
    float GetReloadingProgress() { return IsValid() ? SafeGetField<float>(instance, 0x2C, 0.0f) : 0.0f; }
    float GetCurrentSlow() { return IsValid() ? SafeGetField<float>(instance, 0x30, 0.0f) : 0.0f; }
    int GetTotalAmmo() { return IsValid() ? SafeGetField<int>(instance, 0x34, 0) : 0; }
    int GetBulletsLoaded() { return IsValid() ? SafeGetField<int>(instance, 0x38, 0) : 0; }
    int GetCurrentBombs() { return IsValid() ? SafeGetField<int>(instance, 0x3C, 0) : 0; }
    int GetJumps() { return IsValid() ? SafeGetField<int>(instance, 0x40, 0) : 0; }
    int GetJumpsUsed() { return IsValid() ? SafeGetField<int>(instance, 0x44, 0) : 0; }
    void* GetRefs() { return IsValid() ? SafeGetField<void*>(instance, 0x48, nullptr) : nullptr; }
    float GetSinceJump() { return IsValid() ? SafeGetField<float>(instance, 0x50, 0.0f) : 0.0f; }
    float GetSinceGroundedOrJumped() { return IsValid() ? SafeGetField<float>(instance, 0x54, 0.0f) : 0.0f; }
    float GetSinceGrounded() { return IsValid() ? SafeGetField<float>(instance, 0x58, 0.0f) : 0.0f; }
    void* GetGroundTransform() { return IsValid() ? SafeGetField<void*>(instance, 0x60, nullptr) : nullptr; }
    Vector3 GetGroundNormal() { return IsValid() ? SafeGetField<Vector3>(instance, 0x68, Vector3()) : Vector3(); }
    Vector3 GetGroundPos() { return IsValid() ? SafeGetField<Vector3>(instance, 0x74, Vector3()) : Vector3(); }
    bool GetIsGrounded() { return IsValid() ? SafeGetField<bool>(instance, 0x80, false) : false; }
    bool GetIsCrouching() { return IsValid() ? SafeGetField<bool>(instance, 0x81, false) : false; }
    Vector3 GetPositionDelta() { return IsValid() ? SafeGetField<Vector3>(instance, 0x84, Vector3()) : Vector3(); }
    Vector3 GetLastPos() { return IsValid() ? SafeGetField<Vector3>(instance, 0x90, Vector3()) : Vector3(); }
    float GetGroundedFor() { return IsValid() ? SafeGetField<float>(instance, 0x9C, 0.0f) : 0.0f; }
    float GetCurrentHealthPercentage() { return IsValid() ? SafeGetField<float>(instance, 0xA0, 0.0f) : 0.0f; }
    bool GetInFarm() { return IsValid() ? SafeGetField<bool>(instance, 0xA4, false) : false; }
    void* GetCurrentSeat() { return IsValid() ? SafeGetField<void*>(instance, 0xA8, nullptr) : nullptr; }
    void* GetCurrentHeldObject() { return IsValid() ? SafeGetField<void*>(instance, 0xB0, nullptr) : nullptr; }
    int GetColourPrimary() { return IsValid() ? SafeGetField<int>(instance, 0xB4, 0) : 0; }
    int GetColourSecondary() { return IsValid() ? SafeGetField<int>(instance, 0xB8, 0) : 0; }
    int GetArmorIndex() { return IsValid() ? SafeGetField<int>(instance, 0xBC, 0) : 0; }
    int GetCauseOfDeath() { return IsValid() ? SafeGetField<int>(instance, 0xC0, 0) : 0; }
    bool GetPlayerActive() { return IsValid() ? SafeGetField<bool>(instance, 0xC4, false) : false; }
    int GetPlayerRange() { return IsValid() ? SafeGetField<int>(instance, 0xC8, 0) : 0; }
    int GetFramesCulled() { return IsValid() ? SafeGetField<int>(instance, 0xCC, 0) : 0; }
    float GetIceSpeedM() { return IsValid() ? SafeGetField<float>(instance, 0xD0, 0.0f) : 0.0f; }
    bool GetGroundedThisFrame() { return IsValid() ? SafeGetField<bool>(instance, 0xD4, false) : false; }
    float GetHeight() { return IsValid() ? SafeGetField<float>(instance, 0xD8, 0.0f) : 0.0f; }
    bool GetIsDriver() { return IsValid() ? SafeGetField<bool>(instance, 0xDC, false) : false; }
    float GetSinceDealDamage() { return IsValid() ? SafeGetField<float>(instance, 0xE0, 0.0f) : 0.0f; }
    bool GetIsGhost() { return IsValid() ? SafeGetField<bool>(instance, 0xE4, false) : false; }
    int GetCurrentBandage() { return IsValid() ? SafeGetField<int>(instance, 0xE8, 0) : 0; }
    bool GetIsChanneling() { return IsValid() ? SafeGetField<bool>(instance, 0xEC, false) : false; }
    bool GetBeingChannelled() { return IsValid() ? SafeGetField<bool>(instance, 0xED, false) : false; }
    float GetChannelProgress() { return IsValid() ? SafeGetField<float>(instance, 0xF0, 0.0f) : 0.0f; }
    float GetCancelChannelProgress() { return IsValid() ? SafeGetField<float>(instance, 0xF4, 0.0f) : 0.0f; }

    std::string GetChannelActionName() {
        if (!IsValid()) return "";
        auto str = SafeGetField<Il2CppString*>(instance, 0xF8, nullptr);
        return str && IsValidString(str) ? Il2CppStringToStdString(str) : "";
    }

    float GetSpeedM() { return IsValid() ? SafeGetField<float>(instance, 0x100, 0.0f) : 0.0f; }
    int GetCurrentWeaponID() { return IsValid() ? SafeGetField<int>(instance, 0x104, 0) : 0; }
    void* GetBelovedHorse() { return IsValid() ? SafeGetField<void*>(instance, 0x108, nullptr) : nullptr; }
    bool GetIsChatting() { return IsValid() ? SafeGetField<bool>(instance, 0x110, false) : false; }

    std::string GetCurrentChatMessage() {
        if (!IsValid()) return "";
        auto str = SafeGetField<Il2CppString*>(instance, 0x118, nullptr);
        return str && IsValidString(str) ? Il2CppStringToStdString(str) : "";
    }

    bool GetAllowTK() { return IsValid() ? SafeGetField<bool>(instance, 0x120, false) : false; }
    bool GetIsCharging() { return IsValid() ? SafeGetField<bool>(instance, 0x121, false) : false; }
    float GetCurrentCharge() { return IsValid() ? SafeGetField<float>(instance, 0x124, 0.0f) : 0.0f; }
    int GetFramesSinceCharging() { return IsValid() ? SafeGetField<int>(instance, 0x128, 0) : 0; }
    float GetCurrentIceTime() { return IsValid() ? SafeGetField<float>(instance, 0x12C, 0.0f) : 0.0f; }
    void* GetDataStrings() { return IsValid() ? SafeGetField<void*>(instance, 0x130, nullptr) : nullptr; }
    void* GetCurrentPing() { return IsValid() ? SafeGetField<void*>(instance, 0x138, nullptr) : nullptr; }

    void* GetInstance() const { return instance; }

private:
    void* instance;
};