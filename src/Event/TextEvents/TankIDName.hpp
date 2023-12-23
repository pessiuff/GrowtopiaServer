#pragma once

#include <Event/EventType.hpp>
#include <Packet/TextFunction.hpp>
#include <Packet/VariantFunction.hpp>
#include <Utils/MiscUtils.hpp>
#include <Manager/Database/Database.hpp>
#include <Manager/Item/ItemManager.hpp>
#include <Manager/PlayerTribute/PlayerTributeManager.hpp>


EVENT("tankIDName", TankIDName) {
    if (pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_IS_IN) || pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_LOGGED_ON)) {
        CAction::Log(pAvatar->Get(), "`4Warning! `oYou were already logged in?``");
        pAvatar->RequestDisconnect();
        return;
    }
    if (!pAvatar->GetDetail().Serialize(eventParser, false)) {
        pAvatar->RequestDisconnect();
        return;
    }

    PlayerTable* pTable = (PlayerTable*)GetDatabase()->GetTable(DATABASE_PLAYER_TABLE);
    if (!pTable)
        return;

    auto player_login = pTable->LoginPlayer(pAvatar);
    if (player_login.m_result != PlayerLogin::Result::SUCCESS) {
        CAction::Log(pAvatar->Get(), "`oLogin `4failed`o (`4{}`o)!``", player_login.m_data);
        return;
    }

    pAvatar->SetUserId(pTable->GetPlayerID(pAvatar->GetDetail().GetTankIDName()));
    pAvatar->GetDetail().SetFlag(CLIENTFLAG_LOGGED_ON);

    VarList::OnSuperMain(pAvatar->Get(),
        GetItemManager()->GetHash(),
        "ubistatic-a.akamaihd.net",
        "0098/92540187/cache/",
        "cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster",
        "proto=200|choosemusic=audio/mp3/tsirhc.mp3|active_holiday=9|wing_week_day=0|ubi_week_day=0|server_tick=100370549|clash_active=1|drop_lavacheck_faster=1|isPayingUser=0|usingStoreNavigation=1|enableInventoryTab=1|bigBackpack=1|",
        GetPlayerTributeManager()->GetHash());

	CAction::Log(pAvatar->Get(), "`oLogged in `2successfully`o!``");
}