#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/TextFunction.hpp>

ACTION_EVENT("quit", Quit) {
	// idk?
	if (pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_IS_IN)) {
		pAvatar->RequestDisconnect();
	}
}