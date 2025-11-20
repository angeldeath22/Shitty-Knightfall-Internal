#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include "il2cpp-api-types.h"
#include "PhotonPlayer.hpp"

class PhotonView {
public:
    PhotonView(void* instance) : instance(instance) {}

    static std::shared_ptr<PhotonView> Get(void* component);
    static std::shared_ptr<PhotonView> Get(std::shared_ptr<void> gameObject);
    static std::shared_ptr<PhotonView> Find(int32_t viewID);

    int32_t GetOwnerActorNr();
    int32_t GetViewID();
    bool GetIsMine();
    bool GetAmOwner();
    std::shared_ptr<PhotonPlayer> GetOwner();
    std::shared_ptr<PhotonPlayer> GetController();

    void RequestOwnership();
    void TransferOwnership(std::shared_ptr<PhotonPlayer> newOwner);
    void TransferOwnership(int32_t newOwnerId);

    void* GetInstance() const { return instance; }

private:
    void* instance;
};