#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Manager/PlayerTribute/PlayerTributeManager.hpp>
#include <Packet/PacketFactory.hpp>

ACTION_EVENT("refresh_player_tribute_data", RefreshPlayerTributeData) {
	if (!pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_LOGGED_ON)) {
		pAvatar->RequestDisconnect();
		return;
	}

	pAvatar->GetDetail().SetFlag(CLIENTFLAG_UPDATING_TRIBUTE);
	auto packet_tank = SPlayerTributeUpdatePacket(GetPlayerTributeManager()->GetData(), GetPlayerTributeManager()->GetSize());
	ENetWrapper::SendPacket(pAvatar->Get(), packet_tank);
}