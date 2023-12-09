#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/TextFunction.hpp>

ACTION_EVENT("quit", Quit) {
	// idk?
	pAvatar->RequestDisconnect();
}