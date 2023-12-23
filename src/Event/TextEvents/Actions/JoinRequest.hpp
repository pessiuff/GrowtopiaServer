#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/VariantFunction.hpp>
#include <algorithm>
#include <regex>
#include <memory>
#include <World/WorldPool.hpp>
#include <World/World.hpp>
#include <Logger/Logger.hpp>

ACTION_EVENT("join_request", JoinRequest) {
	if (!pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_IS_IN)) {
		pAvatar->RequestDisconnect();
		return;
	}

	std::string world_name = eventParser.Get("name");
	std::transform(world_name.begin(), world_name.end(), world_name.begin(), ::toupper);

	if (world_name.empty())
		world_name = "START";
	
	if (world_name.length() > 24) {
		VarList::OnConsoleMessage(pAvatar->Get(), "Sorry, the world name is too long!");
		VarList::OnFailedToEnterWorld(pAvatar->Get(), true);
	}

	if (world_name == "EXIT" || !std::regex_match(world_name, std::regex{ "^[A-Z0-9]+$" })) {\
		VarList::OnConsoleMessage(pAvatar->Get(), "Sorry, spaces and special characters are not allowed in world or door names. Try again.");
		VarList::OnFailedToEnterWorld(pAvatar->Get(), true);
		return;
	}

	WorldPool* worldPool = GetWorldPool();
	std::shared_ptr<World> world = worldPool->GetWorld(world_name);

	if (!world)
		world = worldPool->NewWorld(world_name);
	
	if (world->HasPlayer(pAvatar)) {
		world->RemovePlayer(pAvatar);
		VarList::OnFailedToEnterWorld(pAvatar->Get(), true);
		return;
	}

	uint8_t* data = world->Serialize();
	size_t size = world->GetMemoryUsage();

	auto packet_world = SSendMapDataPacket(data, size);
	ENetWrapper::SendPacket(pAvatar->Get(), packet_world);

	const auto& spawn_pos { world->GetTilePos(ITEMTYPE_MAIN_DOOR) };
	pAvatar->SetWorld(world_name);
	pAvatar->SetNetId(world->AddPlayer(pAvatar));
	pAvatar->SetPosition(spawn_pos.X * 32 + 4 /* add 4 to spawn in middle of x block? */, spawn_pos.Y * 32);
	
	auto packet_inventory = SSendInventoryStatePacket(pAvatar->GetItems()->Serialize());
	ENetWrapper::SendPacket(pAvatar->Get(), packet_inventory);

	VarList::OnSpawn(pAvatar->Get(), pAvatar->GetSpawnData(true));
	VarList::OnSetClothing(pAvatar->Get(), pAvatar->GetItems()->GetClothes(), pAvatar->GetItems()->GetSkinColor(), false, pAvatar->GetNetId());
	pAvatar->SendCharacterState(pAvatar);

	world->Broadcast([&](Player* target) {
		if (target->GetUserId() == pAvatar->GetUserId()) {
			return;
		}

		VarList::OnSpawn(pAvatar->Get(), target->GetSpawnData(false));
		VarList::OnSetClothing(pAvatar->Get(), target->GetItems()->GetClothes(), target->GetItems()->GetSkinColor(), false, target->GetNetId());
		pAvatar->SendCharacterState(target);

		VarList::OnSpawn(target->Get(), pAvatar->GetSpawnData(false));
		VarList::OnSetClothing(target->Get(), pAvatar->GetItems()->GetClothes(), pAvatar->GetItems()->GetSkinColor(), false, pAvatar->GetNetId());
		target->SendCharacterState(pAvatar);
	});
}