#include <Manager/Item/ItemManager.hpp>
#include <Logger/Logger.hpp>
#include <Utils/BinaryReader.hpp>
#include <Utils/FileManager.hpp>

ItemManager g_itemManager;
ItemManager* GetItemManager() {
    return &g_itemManager;
}

bool ItemManager::Serialize() {
    if (!std::filesystem::exists("cache/items.dat"))
        return false;
    auto itemData = FileManager::ReadAsByteArray("cache/items.dat");
    if (!itemData.data() || itemData.empty())
        return false;

    m_data = itemData;

    auto start = std::chrono::high_resolution_clock::now();

    BinaryReader br(itemData.data());
    m_version = br.Read<uint16_t>();
    m_itemCount = br.Read<uint32_t>();

    m_hash = Utils::GetProtonHash(itemData.data(), itemData.size());

    m_items.reserve(m_itemCount);
    for (auto index = 0; index < m_itemCount; index++) {
        auto* item = m_items.emplace_back(new ItemInfo{});
        item->Serialize(br);

        if (index != item->m_Id) {
        	Logger::Print(WARNING, "{} >> Incorrect item entry found. ID: {}", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "ItemManager"), item->m_Id);
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    Logger::Print(INFO, "{} >> Serialized items.dat ({}ms elapsed) (Version {}) with {} items loaded.", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "ItemManager"), std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), m_version, this->GetItemsLoaded());
    return true;
}
void ItemManager::Encode() {
    std::size_t alloc = 6;
    for (ItemInfo* item : m_items)
        alloc += item->GetMemoryUsage() + 20;

    BinaryWriter buffer(alloc);
    buffer.Write<uint16_t>(this->m_version);
    buffer.Write<uint32_t>(this->m_itemCount);
    for (ItemInfo* item : m_items)
        item->Pack(buffer);

    FileManager::WriteAsBytes("cache/items.dat", reinterpret_cast<char*>(buffer.Get()), buffer.GetPosition());
}
void ItemManager::Kill() {
    for (auto& item : m_items) {
        if (!item)
            continue;
        delete item;
        item = nullptr;
    }
    m_items.clear();
}

ItemInfo* ItemManager::GetItem(uint32_t itemId) {
    if (itemId < 0 || itemId > m_items.size())
        return nullptr;
    return m_items[itemId];
}

std::vector<ItemInfo*> ItemManager::GetItems() {
    return m_items;
}
size_t ItemManager::GetItemsLoaded() {
    return m_items.size();
}

uint32_t ItemManager::GetHash() {
    return m_hash;
}


