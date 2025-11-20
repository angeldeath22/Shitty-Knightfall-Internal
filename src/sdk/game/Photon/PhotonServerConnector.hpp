#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "il2cpp-api-types.h"

class PhotonServerConnector {
public:
    PhotonServerConnector(void* instance_ptr) {
        instance = instance_ptr;
    }


    static std::shared_ptr<PhotonServerConnector> GetStaticInstance();


    std::string GetUserID();
    int32_t GetUserColour();
    int32_t GetUserArmor();
    std::string GetPlayerName();
    void SetPlayerName(const std::string& name);

    void* GetInstance() const { return instance; }

private:
    void* instance;
};