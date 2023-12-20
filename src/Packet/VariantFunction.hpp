#pragma once
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/VariantList.hpp>
#include <Utils/TextParse.hpp>
#include <Utils/Math.hpp>
#include <Manager/Item/ItemType.hpp>

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
    static VariantList OnRequestWorldSelectMenu(ENetPeer* peer, std::string data, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(data);

        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnFailedToEnterWorld(ENetPeer* peer, bool value, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(value ? 1: 0);

        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnSpawn(ENetPeer* peer, TextParse data, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(data.GetAsString());

        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnSetClothing(ENetPeer* peer, std::array<uint16_t, NUM_BODY_PARTS> cloth, const Color color, bool sound, uint32_t net_id, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS, net_id);
        vList.Insert(CL_Vec3<float> { static_cast<float>(cloth[CLOTHTYPE_HAIR]), static_cast<float>(cloth[CLOTHTYPE_SHIRT]), static_cast<float>(cloth[CLOTHTYPE_PANTS]) });
        vList.Insert(CL_Vec3<float> { static_cast<float>(cloth[CLOTHTYPE_FEET]), static_cast<float>(cloth[CLOTHTYPE_FACE]), static_cast<float>(cloth[CLOTHTYPE_HAND]) });
        vList.Insert(CL_Vec3<float> { static_cast<float>(cloth[CLOTHTYPE_BACK]), static_cast<float>(cloth[CLOTHTYPE_MASK]), static_cast<float>(cloth[CLOTHTYPE_NECKLACE]) });
        vList.Insert(color.GetInt());
        vList.Insert(CL_Vec3<float> { static_cast<float>(cloth[CLOTHTYPE_ANCES]), static_cast<float>(sound), static_cast<float>(0) });

        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnRemove(ENetPeer* peer, uint16_t netId, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(fmt::format("netID|{}", netId));

        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
};