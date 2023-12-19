#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/TextFunction.hpp>
#include <config.hpp>
#include <World/WorldPool.hpp>

ACTION_EVENT("enter_game", EnterGame) {
	if (!pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_LOGGED_ON)) {
		pAvatar->RequestDisconnect();
		return;
	}
	
	pAvatar->GetDetail().RemoveFlag(CLIENTFLAG_UPDATING_ITEMS);
	pAvatar->GetDetail().RemoveFlag(CLIENTFLAG_UPDATING_TRIBUTE);
	pAvatar->GetDetail().SetFlag(CLIENTFLAG_IS_IN);

	CAction::Log(pAvatar->Get(), "`oWelcome back ``{}`o, {} `wV{}``", pAvatar->GetDisplayName(), Configuration::GetName(), Configuration::GetVersion());
	GetWorldPool()->SendWorldOffer(pAvatar);
}