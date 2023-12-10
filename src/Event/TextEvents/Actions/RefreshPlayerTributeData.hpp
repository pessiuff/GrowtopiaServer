#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Manager/PlayerTribute/PlayerTributeManager.hpp>
#include <Packet/PacketFactory.hpp>

ACTION_EVENT("refresh_player_tribute_data", RefreshPlayerTributeData) {
	auto packet_tank = SPlayerTributeUpdatePacket(GetPlayerTributeManager()->GetData(), GetPlayerTributeManager()->GetSize());
	ENetWrapper::SendPacket(pAvatar->Get(), packet_tank);
}