#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <Packet/GameUpdatePacket.hpp>
#include <Packet/VariantList.hpp>
#include <Utils/BinaryWriter.hpp>
#include <Logger/Logger.hpp>
#include <Player/Player.hpp>

class IPacketType {
public:
    uint32_t m_packetType;
};

class ISPacket : public IPacketType {
public:
    std::vector<uint8_t>    m_packetData    = {};
    std::size_t             m_packetLength  = 0;
};

class STankPacket : public ISPacket {
public:
    STankPacket(TankPacketData tankData) : m_tankData(std::move(tankData)) { 
        m_packetType = NET_MESSAGE_GAME_PACKET; 
        this->Pack();
    }

public:
    void Pack() {
        m_packetData.reserve(sizeof(TankPacketData) + m_tankData.m_dataLength);
        m_packetLength = sizeof(TankPacketData) + m_tankData.m_dataLength;

        std::memcpy(m_packetData.data(), &m_tankData, sizeof(TankPacketData));
        if (m_tankData.m_dataLength > 0)
            std::memcpy(m_packetData.data() + sizeof(TankPacketData), m_data.data(), m_tankData.m_dataLength);
    }

protected:
    TankPacketData m_tankData;
    
public:
    std::vector<uint8_t> m_data;
};

/*
    TANK PACKETS
*/
class SVariantPacket : public STankPacket {
public:
    SVariantPacket(VariantList vList) : STankPacket(TankPacketData()), m_vList(vList) {
        m_tankData.m_type = NET_GAME_PACKET_CALL_FUNCTION;
        m_tankData.m_flags.bExtended = true;
        m_tankData.m_netId = vList.netId;
        m_tankData.m_delay = vList.executionDelay;
        m_tankData.m_dataLength = vList.GetMemoryUsage();

        auto packedData = vList.Pack();
        m_data.reserve(m_tankData.m_dataLength);

        std::memcpy(m_data.data(), packedData, m_tankData.m_dataLength);
        STankPacket::Pack();
    }

private:
    VariantList m_vList;
};

class SItemDataUpdatePacket : public STankPacket {
public:
    SItemDataUpdatePacket(std::vector<uint8_t> data) : STankPacket(TankPacketData()) {
        m_tankData.m_type = NET_GAME_PACKET_SEND_ITEM_DATABASE_DATA;
        m_tankData.m_flags.bExtended = true;
        m_tankData.m_netId = -1;
        m_tankData.m_dataLength = data.size();

        m_data.reserve(m_tankData.m_dataLength);
        std::memcpy(m_data.data(), data.data(), m_tankData.m_dataLength);

        STankPacket::Pack();
    }
};

class SPlayerTributeUpdatePacket : public STankPacket {
public:
    SPlayerTributeUpdatePacket(uint8_t* data, uint32_t size) : STankPacket(TankPacketData()) {
        m_tankData.m_type = NET_GAME_PACKET_SEND_PLAYER_TRIBUTE_DATA;
        m_tankData.m_flags.bExtended = true;
        m_tankData.m_netId = -1;
        m_tankData.m_dataLength = size;

        m_data.reserve(m_tankData.m_dataLength);
        std::memcpy(m_data.data(), data, m_tankData.m_dataLength);

        STankPacket::Pack();
    }
};

class SSendMapDataPacket : public STankPacket {
public:
    SSendMapDataPacket(uint8_t* data, size_t size) : STankPacket(TankPacketData()) {
        m_tankData.m_type = NET_GAME_PACKET_SEND_MAP_DATA;
        m_tankData.m_flags.bExtended = true;
        m_tankData.m_netId = -1;
        m_tankData.m_dataLength = static_cast<uint32_t>(size);

        m_data.reserve(m_tankData.m_dataLength);
        std::memcpy(m_data.data(), data, m_tankData.m_dataLength);

        STankPacket::Pack();
    }
};

class SSendInventoryStatePacket : public STankPacket {
public:
    SSendInventoryStatePacket(std::vector<uint8_t> data) : STankPacket(TankPacketData()) {
        m_tankData.m_type = NET_GAME_PACKET_SEND_INVENTORY_STATE;
        m_tankData.m_flags.bExtended = true;
        m_tankData.m_netId = -1;
        m_tankData.m_dataLength = static_cast<uint32_t>(data.size());

        m_data.reserve(m_tankData.m_dataLength);
        std::memcpy(m_data.data(), data.data(), m_tankData.m_dataLength);

        STankPacket::Pack();
    }
};

class SSetCharacterState : public STankPacket {
public:
    SSetCharacterState(Player* player) : STankPacket(TankPacketData()) {
        m_tankData.m_type = NET_GAME_PACKET_SET_CHARACTER_STATE;
        m_tankData.m_netId = player->GetNetId();
        m_tankData.m_punchIndex = player->GetPunchID();
        m_tankData.m_buildRange = player->GetBuildRange();
        m_tankData.m_punchRange = player->GetPunchRange();
        m_tankData.m_waterSpeed = player->GetWaterSpeed();
        m_tankData.m_effectFlags = player->GetFlags();
        m_tankData.m_acceleration = player->GetAcceleration();
        m_tankData.m_punchStrength = player->GetPunchStrength();
        m_tankData.m_speedOut = player->GetSpeed();
        m_tankData.m_gravityOut = player->GetGravity();
        m_tankData.m_pupilColor = player->GetPupilColor().GetInt();
        m_tankData.m_hairColor = player->GetHairColor().GetInt();
        m_tankData.m_eyesColor = player->GetEyesColor().GetInt();

        STankPacket::Pack();
    }
};

/*
    PACKETS
*/
class SLoginInformationRequestPacket : public ISPacket {
public:
    SLoginInformationRequestPacket() {
        m_packetType = NET_MESSAGE_SERVER_HELLO;
    }
};

/*
    TEXT PACKETS
*/
class STextPacket : public ISPacket {
public:
    STextPacket(std::string data) : m_data(std::move(data)) {
        m_packetType = NET_MESSAGE_GAME_MESSAGE;

        m_packetData.reserve(m_data.size());
        m_packetLength = m_data.size();

        std::memcpy(m_packetData.data(), m_data.data(), m_data.size());
    }

private:
    std::string m_data;
};