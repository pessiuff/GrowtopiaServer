#include <Player/PlayerItems.hpp>
#include <Manager/Item/ItemComponent.hpp>
#include <Manager/Item/ItemManager.hpp>

PlayerItems::PlayerItems(ENetPeer* pPeer) : m_pPeer(pPeer) {
    for (auto index = 0; index < NUM_BODY_PARTS; index++)
        m_clothes[index] = Item::BLANK;
    m_skinColor = Color(0xB4, 0x8A, 0x78, 0xFF);
    m_gems = 0;

    m_backpackSpace = 20;
    this->AddItem(Item::FIST, 1);
    this->AddItem(Item::WRENCH, 1);
}

int32_t PlayerItems::GetGems() const {
    return m_gems;
}
void PlayerItems::SetGems(int32_t gems) {
    m_gems = gems;
}

uint16_t& PlayerItems::GetCloth(eClothTypes bodyPart) {
    return m_clothes[bodyPart];
}
std::array<uint16_t, NUM_BODY_PARTS>& PlayerItems::GetClothes() {
    return m_clothes;
}
void PlayerItems::SetCloth(eClothTypes bodyPart, uint16_t itemId) {
    if (static_cast<int32_t>(bodyPart) < Item::BLANK || static_cast<int32_t>(bodyPart) > NUM_BODY_PARTS)
        return;
    m_clothes[bodyPart] = itemId;
}

Color PlayerItems::GetSkinColor() const {
    return m_skinColor;
}

bool PlayerItems::AddItem(uint16_t itemId, uint8_t count) {
    if (count < 1)
        return false;
    if (auto it = m_bpItems.find(itemId); it != m_bpItems.end()) {
        auto pItem = GetItemManager()->GetItem(itemId);
        if (!pItem)
            return false;
        if ((it->second + count) > pItem->m_maxAmount)
            return false;
        it->second += count;
    }
    else {
        if (m_bpItems.size() >= m_backpackSpace)
            return false;
        m_bpItems.insert_or_assign(itemId, count);
    }
    /*if (send_packet)
        this->Update(item_id, count, true);*/
    return true;
}

std::vector<uint8_t> PlayerItems::Serialize() const {
    std::vector<uint8_t> return_data {};
    std::size_t size = 8 + (4 * m_bpItems.size());
    return_data.resize(size);

    BinaryWriter writer(return_data.data());
    writer.Write<uint8_t>(0x1); // inventory version
    writer.Write<uint32_t>(m_backpackSpace);
    writer.Write<uint16_t>(static_cast<uint16_t>(m_bpItems.size()));

    for (const auto& item : m_bpItems) {
        uint8_t flags = INVENTORY_ITEM_FLAGS_NONE; // irrelevant
        writer.Write<uint16_t>(item.first);
        writer.Write<uint8_t>(item.second);
        writer.Write<uint8_t>(flags);
    }

    return return_data;
}
