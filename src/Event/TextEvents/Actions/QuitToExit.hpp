#pragma once

#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>

ACTION_EVENT("quit_to_exit", QuitToExit) {
    const auto& world = GetWorldPool()->GetWorld(pAvatar->GetWorld());

    world->Broadcast([&](Player* target) {
        if (target->GetNetId() == pAvatar->GetNetId())
			return;
        VarList::OnRemove(target->Get(), pAvatar->GetNetId());
    });

    world->RemovePlayer(pAvatar);
    pAvatar->SetWorld("EXIT");

    GetWorldPool()->SendWorldOffer(pAvatar);
}