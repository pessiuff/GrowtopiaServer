#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/TextFunction.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Manager/Item/ItemManager.hpp>
#include <Packet/PacketFactory.hpp>

ACTION_EVENT("refresh_item_data", RefreshItemData) {
	CAction::Log(pAvatar->Get(), "`oOne moment, updating item data...``");
	auto packet_tank = SItemDataUpdatePacket(GetItemManager()->GetData());
	ENetWrapper::SendPacket(pAvatar->Get(), packet_tank);
}