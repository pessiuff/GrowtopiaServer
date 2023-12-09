#pragma once

#include <Event/EventType.hpp>
#include <Packet/TextFunction.hpp>
#include <Utils/MiscUtils.hpp>
#include <Manager/Database/Database.hpp>
#include <fmt/format.h>
#include <Logger/Logger.hpp>

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

    Logger::Print(INFO, "Name: {}", eventParser.Get("tankIDName", 1));
    Logger::Print(INFO, "Pass: {}", eventParser.Get("tankIDPass", 1));

    PlayerTable* pTable = (PlayerTable*)GetDatabase()->GetTable(DATABASE_PLAYER_TABLE);
    if (!pTable)
        return;

    auto player_login = pTable->LoginPlayer(pAvatar);
    if (player_login.m_result != PlayerLogin::Result::SUCCESS) {
        CAction::Log(pAvatar->Get(), fmt::format("`oLogin `4failed`o (`4{}`o)!``", player_login.m_data));
        return;
    }

    //pAvatar->GetDetail().SetFlag(CLIENTFLAG_LOGGED_ON);
	CAction::Log(pAvatar->Get(), "`oLogged in `2successfully`o!``");
}