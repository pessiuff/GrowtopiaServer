#pragma once
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/VariantList.hpp>

class VarList {
public:
    static VariantList OnSuperMain(ENetPeer* peer, uint32_t items_dat_hash, std::string cdn_host, std::string cdn_cache_path, std::string blocked, std::string settings, uint16_t player_tribute_hash, int32_t delayMS = 0) {
        auto vList = VariantList::Create("OnSuperMainStartAcceptLogonHrdxs47254722215a", delayMS);
        vList.Insert(items_dat_hash);
        vList.Insert(cdn_host);
        vList.Insert(cdn_cache_path);
        vList.Insert(blocked);
        vList.Insert(settings);
        if (player_tribute_hash != NULL)
            vList.Insert(player_tribute_hash);

        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnConsoleMessage(ENetPeer* peer, std::string message, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(message);
        
        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnTextOverlay(ENetPeer* peer, std::string message, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(message);
        
        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList SetHasGrowID(ENetPeer* peer, bool checkboxEnable, std::string tankIDName, std::string tankIDPass, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(checkboxEnable ? 1 : 0);
        vList.Insert(tankIDName);
        vList.Insert(tankIDPass);
        
        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
};