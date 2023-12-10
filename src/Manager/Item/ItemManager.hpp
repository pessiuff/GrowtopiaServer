#pragma once
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <Manager/Item/ItemInfo.hpp>
#include <Utils/MiscUtils.hpp>

class ItemManager {
public:    
    bool Serialize();
    void Encode();
    void Kill();
    
    std::vector<uint8_t> GetData() { return m_data; };

    ItemInfo* GetItem(uint32_t itemId);

    std::vector<ItemInfo*> GetItems();
    size_t GetItemsLoaded();

    uint32_t GetHash();

public:
    ItemManager() = default;
    ~ItemManager() = default;

private:
    std::vector<uint8_t> m_data;
    size_t m_size;

    uint16_t m_version;
    uint32_t m_itemCount;

    uint32_t m_hash;
    
    std::vector<ItemInfo*> m_items;
};

ItemManager* GetItemManager();