#pragma once
#include <Event/EventType.hpp>
#include <Packet/TextFunction.hpp>
#include <Utils/MiscUtils.hpp>

EVENT("requestedName", OnRequestedName) {
    if (!pAvatar->GetDetail().Serialize(eventParser, true)) {
        pAvatar->RequestDisconnect();
        return;
    }

    pAvatar->PlayerDialog::Send(DIALOG_TYPE_REGISTRATION, TextParse{});
}