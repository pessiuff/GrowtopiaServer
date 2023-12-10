#include <Manager/PlayerTribute/PlayerTributeManager.hpp>

PlayerTributeManager g_playerTributeManager;
PlayerTributeManager* GetPlayerTributeManager() {
    return &g_playerTributeManager;
}

void PlayerTributeManager::Build() {
    std::string playerTribute {
        fmt::format(
            "`oDeveloper: `psix\n"
        )
    };

    std::string mentorTribute {
		fmt::format(
			"`oTest\n"
		)
	};

    m_size = sizeof(uint32_t) + playerTribute.length() + mentorTribute.length();
    m_data = static_cast<char*>(std::malloc(m_size));

    BinaryWriter writer(reinterpret_cast<uint8_t*>(m_data));
    writer.Write<uint16_t>(static_cast<uint16_t>(playerTribute.length()));
    writer.Write(playerTribute);
    writer.Write<uint16_t>(static_cast<uint16_t>(mentorTribute.length()));
    writer.Write(mentorTribute);

    m_hash = Utils::GetProtonHash(writer.Get(), m_size);

    Logger::Print(INFO, "PlayerTributeManager - Hash: {} | Data: {}", m_hash, sizeof(m_data));
}

void PlayerTributeManager::Kill() {
std::free(m_data);
	m_data = nullptr;
	m_hash = 0;
}