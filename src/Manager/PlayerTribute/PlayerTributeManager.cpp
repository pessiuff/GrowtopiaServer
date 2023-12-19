#include <Manager/PlayerTribute/PlayerTributeManager.hpp>

PlayerTributeManager g_playerTributeManager;
PlayerTributeManager* GetPlayerTributeManager() {
    return &g_playerTributeManager;
}

void PlayerTributeManager::Build() {
    std::string epic_players {
        fmt::format(
            "`oDeveloper: `psix``"
        )
    };

    std::string exceptional_mentors {
		fmt::format(
			"`oTest``"
		)
	};

    std::string charity_champions {
        fmt::format(
            "`oTest``"
        )
    };

    m_size = sizeof(uint32_t) + epic_players.length() + exceptional_mentors.length() + charity_champions.length();
    m_data = static_cast<char*>(std::malloc(m_size));

    BinaryWriter writer(reinterpret_cast<uint8_t*>(m_data));
    writer.Write<uint16_t>(static_cast<uint16_t>(epic_players.length()));
    writer.Write(epic_players.c_str(), epic_players.length());
    writer.Write<uint16_t>(static_cast<uint16_t>(exceptional_mentors.length()));
    writer.Write(exceptional_mentors.c_str(), exceptional_mentors.length());
    writer.Write<uint16_t>(static_cast<uint16_t>(charity_champions.length()));
    writer.Write(charity_champions.c_str(), charity_champions.length());

    m_hash = Utils::GetProtonHash(writer.Get(), m_size);

    Logger::Print(INFO, "PlayerTributeManager Built - Hash: {} | Data: {}", m_hash, sizeof(m_data));
}

void PlayerTributeManager::Kill() {
std::free(m_data);
	m_data = nullptr;
	m_hash = 0;
}