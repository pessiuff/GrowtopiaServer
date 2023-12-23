#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Utils/Math.hpp>

TANK_EVENT("OnMovement", OnMovement) {
	if (pAvatar->GetWorld() == "EXIT") return;

	const auto& world = GetWorldPool()->GetWorld(pAvatar->GetWorld());

	CL_Vec2<int> position = { (int) pTankData->m_positionX / 32, (int) pTankData->m_positionY / 32 };

    if (position.X > world->GetSize().X || position.Y > world->GetSize().Y)
		return;

	pTankData->m_netId = pAvatar->GetNetId();
	pAvatar->SetPosition(pTankData->m_positionX, pTankData->m_positionY);

	if (pTankData->m_flags.bFacingLeft) {
		pAvatar->GetDetail().SetFlag(eClientFlags::CLIENTFLAG_IS_FACING_LEFT);
	}
	else {
		pAvatar->GetDetail().RemoveFlag(eClientFlags::CLIENTFLAG_IS_FACING_LEFT);
	}

	auto packet = STankPacket(*pTankData);

	world->Broadcast([&](Player* target) {
		ENetWrapper::SendPacket(target->Get(), eNetMessageType::NET_MESSAGE_GAME_PACKET, packet.m_packetData.data(), packet.m_packetLength);
	});
}