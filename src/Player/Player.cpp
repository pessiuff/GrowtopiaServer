#include <Player/Player.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/PacketFactory.hpp>
#include <Logger/Logger.hpp>
#include <Utils/Math.hpp>

Player::Player(ENetPeer* peer) : Peer(peer),
    PlayerDialog(peer),
    m_flags(0),
    m_detail(), m_items(peer) {
        peer->data = std::malloc(sizeof(uint32_t));
        memcpy(peer->data, &peer->connectID, sizeof(uint32_t));
}
Player::~Player() {
    // TODO
}

bool Player::IsFlagOn(ePlayerFlags flag) const {
    if (m_flags & flag)
        return true;
    return false;
}
void Player::SetFlag(ePlayerFlags flag) {
    m_flags |= flag;
}
void Player::RemoveFlag(ePlayerFlags flag) {
    m_flags &= ~flag;
}

uint32_t Player::GetNetId() const {
    return m_netId;
}

void Player::SetNetId(const uint32_t& netId) {
    m_netId = netId;
}

uint32_t Player::GetUserId() const {
    return m_userId;
}
void Player::SetUserId(const uint32_t& userId) {
    m_userId = userId;
}

std::string Player::GetDisplayName() const {
    return fmt::format("{} `w(`2{}`w)``", m_detail.GetTankIDName(), m_netId);
}

std::string Player::GetWorld() const {
    return m_world;
}

void Player::SetWorld(const std::string& world) {
	m_world = world;
}

CL_Vec2<int> Player::GetPosition() {
    return m_position;
}

void Player::SetPosition(const int& x, const int& y) {
    m_position.X = x;
	m_position.Y = y;
}

TextParse Player::GetSpawnData(const bool& local) {
    TextParse data;
    data.Add("spawn", "avatar");
    data.Add("netID", GetNetId());
    data.Add("userID", GetUserId());
    data.Add("colrect", _CL_Recti { 0, 0, 20, 30 });
    data.Add("posXY", CL_Vec2<int> { GetPosition().X, GetPosition().Y });
    data.Add("name", GetDisplayName());
    data.Add("country", GetDetail().GetCountryCode());
    data.Add("invis", IsFlagOn(PLAYERFLAG_IS_INVISIBLE));
    data.Add("mstate", IsFlagOn(PLAYERFLAG_IS_MOD));
    data.Add("smstate", IsFlagOn(PLAYERFLAG_IS_SUPER_MOD));
    data.Add("onlineID", "");

    if (local)
        data.Add("type", "local");

    Logger::Print("{}", data.GetAsString());

    return data;
}

void Player::SendCharacterState(Player* target) {
    auto packet_tank = SSetCharacterState(this);
    ENetWrapper::SendPacket(target->Get(), packet_tank);
}

TankInfo& Player::GetDetail() {
    return m_detail;
}
PlayerItems* Player::GetItems() {
    return &m_items;
}

void Player::OnConnect() {
    Logger::Print(INFO, "A player connected with IP {}, connectId {} and {} pings.", this->GetIp(), this->GetConnectId(), this->GetPing());
    
    auto packet = SLoginInformationRequestPacket();
    ENetWrapper::SendPacket(this->Get(), packet);
}
void Player::OnDisconnect() {
    Logger::Print(INFO, "A player disconnected with IP {}, connectId {} and {} pings.", this->GetIp(), this->GetConnectId(), this->GetPing());
}