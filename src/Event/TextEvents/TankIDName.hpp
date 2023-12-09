#pragma once

#include <Event/EventType.hpp>
#include <Packet/TextFunction.hpp>
#include <Utils/MiscUtils.hpp>

EVENT("tankIDName", TankIDName) {
    if (pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_IS_IN)) {
        CAction::Log(pAvatar->Get(), "`4Warning! `oYou were already logged in?``");
        pAvatar->RequestDisconnect();
        return;
    }
    if (!pAvatar->GetDetail().Serialize(eventParser, false)) {
        pAvatar->RequestDisconnect();
        return;
    }
    pAvatar->SetRawName(pAvatar->GetDetail().GetTankIDName());

    if (!Utils::IsValidUsername(pAvatar->GetRawName()) || (pAvatar->GetRawName().length() < 3 || pAvatar->GetRawName().length() > 10)) {
        CAction::Log(pAvatar->Get(), "`4Oops! `oYour name is including invalid characters, please try again.``");
        pAvatar->RequestDisconnect();
        return;
    }

	CAction::Log(pAvatar->Get(), "`oLogged in `2successfully`o!``");
}