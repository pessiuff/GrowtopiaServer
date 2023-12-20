#pragma once
#include <memory>
#include <enet/enet.h>
#include <ENetWrapper/Peer.hpp>
#include <Protocol/TankInfo.hpp>
#include <Player/PlayerDialog/PlayerDialog.hpp>
#include <Player/PlayerItems.hpp>
#include <Utils/TextParse.hpp>
#include <Player/CharacterState.hpp>

class Player : public Peer, public CharacterState,
               public PlayerDialog {
public:
    explicit Player(ENetPeer* pPeer);
    ~Player();
    
    operator ENetPeer*() { 
        return this->Get();
    }
public:
    bool IsFlagOn(ePlayerFlags flag) const;
    void SetFlag(ePlayerFlags flag);
    void RemoveFlag(ePlayerFlags flag);

    uint32_t GetNetId() const;
    void SetNetId(const uint32_t& netId);

    uint32_t GetUserId() const;
    void SetUserId(const uint32_t& userId);

    std::string GetDisplayName() const;
    void SetDisplayName(const std::string& name);

    std::string GetWorld() const;
    void SetWorld(const std::string& world);

    CL_Vec2<int> GetPosition();
    void SetPosition(const int& x, const int& y);

    TextParse GetSpawnData(const bool& local = false);

    void SendCharacterState(Player* player);

public:
    TankInfo& GetDetail();
    PlayerItems* GetItems();

public:
    void OnConnect();
    void OnDisconnect();

private:
    TankInfo m_detail;
    PlayerItems m_items;

private:
    std::string m_world { "EXIT" };
    CL_Vec2<int> m_position { 0, 0 };

    uint32_t m_netId;
    uint32_t m_userId;
    uint32_t m_flags;

    std::string m_displayName;

    std::string m_emailAddress;
    uint64_t m_discordClientId;
};
