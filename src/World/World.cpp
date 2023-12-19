#include <World/World.hpp>

World::World(const std::string& name, const uint32_t& width, const uint32_t& height) : m_flags(0), m_netID(0), m_name { std::move(name) }, m_width(width), m_height(height) {
}

World::~World() {
	m_tiles.clear();
}

void World::Generate() {
	randutils::mt19937_rng rng;

	const CL_Vec2<int>& world_size = GetSize();

	const CL_Vec2<int>& dirt_layer { 24, 52 }; // start (not included), end (not included)
	const int& rock_layer = 27; // start
	const int& lava_layer = 47; // start
	const int& bedrock_layer = 51; // start

	const CL_Vec2<int> main_door { rng.uniform(0, GetSize().X - 5) + 5, dirt_layer.X}; // start, end

	m_tiles.reserve(GetSize().X * GetSize().Y);
	for (int i = 0; i < GetSize().X * GetSize().Y; i++) {
		CL_Vec2<int> pos { i % 100, i / 100 };
		
		Tile tile {};
		tile.SetPosition(pos);

		if (pos.Y > dirt_layer.X && pos.Y < dirt_layer.Y) {
			if (pos.Y > lava_layer && rng.uniform(0.f, 2.f) < 1.5f) {
				tile.SetForeground(Item::LAVA);
			} else {
				if (pos.Y > rock_layer && rng.uniform(0.f, 1.f) < 0.04f) {
					tile.SetForeground(Item::ROCK);
				} else {
					tile.SetForeground(Item::DIRT);
				}
			}
		} else if (pos.X == main_door.X && pos.Y == main_door.Y) {
			tile.SetForeground(Item::MAIN_DOOR);
			tile.SetBackground(Item::CAVE_BACKGROUND);

			tile.SetFlag(TILEFLAG_TILEEXTRA);
			tile.SetExtraType(TileExtra::TYPE_DOOR);
			tile.m_doorData = TileExtra::Door {
				.m_label = "EXIT"
			};
		} else if (pos.Y > bedrock_layer) {
			tile.SetForeground(Item::BEDROCK);
		}

		if (pos.X == main_door.X && pos.Y == main_door.Y + 1) {
			tile.SetForeground(Item::BEDROCK);
		}

		if (pos.Y > dirt_layer.X) {
			tile.SetBackground(Item::CAVE_BACKGROUND);
		}

		m_tiles.push_back(tile);
	};

}

Tile* World::GetTile(const uint32_t& x, const uint32_t& y) {
	if (x < 0 || y < 0 || x > m_width || y > m_height)
		return nullptr;

	return &m_tiles[x + y * m_width];
}

CL_Vec2<int> World::GetTilePos(const uint16_t& item_id) const {
	for (int i = 0; i < m_tiles.size(); i++) {
		if (m_tiles[i].GetForeground() != item_id)
			continue;
		return { static_cast<int>(i % m_width), static_cast<int>(i / m_width) };
	}
	return { 0, 0 };
}

CL_Vec2<int> World::GetTilePos(const eItemTypes& item_type) const {
	CL_Vec2<int> result { 0, 0};
	for (int i = 0; i < m_tiles.size(); i++) {
		const auto& item = GetItemManager()->GetItem(m_tiles[i].GetForeground());
		if (item->m_itemType != item_type)
			continue;
		result = m_tiles[i].GetPosition();
	}
	return result;
}

uint32_t World::AddPlayer(Player* player) {
	m_netID += 1;
	m_players[m_netID] = player;
	return m_netID;
}

void World::RemovePlayer(Player* player) {
	m_players.erase(player->GetNetId());
}

bool World::HasPlayer(Player* player) {
	for (const auto& pair : m_players) {
		auto world_player { pair.second };
		if (world_player->GetUserId() != player->GetUserId())
			continue;
		return true;
	}
	return false;
}

std::vector<Player*> World::GetPlayers() {
	std::vector<Player*> result_players {};

	for (const auto& pair : m_players)
		result_players.push_back(pair.second);

	return result_players;
}

void World::Broadcast(const std::function<void(Player*)>& func) {
	for (const auto& pair : m_players) {
		func(pair.second);
	}
}

std::size_t World::GetMemoryUsage() const {
	std::size_t size { sizeof(uint16_t) }; // version
	size += sizeof(uint32_t); // flags
	size += sizeof(uint16_t); // name length
	size += m_name.length(); // name
	size += sizeof(uint32_t); // width
	size += sizeof(uint32_t); // height
	size += sizeof(uint32_t); // block count
	// TODO: Try to reverse unknown values
	size += sizeof(uint8_t); // unk 1
	size += sizeof(uint16_t); // unk 2
	size += sizeof(uint16_t); // unk 3

	for (auto& tile : m_tiles)
		size += tile.GetMemoryUsage();

	size += sizeof(uint32_t); // unk 4
	size += sizeof(uint32_t); // unk 5
	size += sizeof(uint32_t); // unk 6

	size += sizeof(uint32_t); // object count
	size += sizeof(uint32_t); // object last id
	size += sizeof(uint32_t); // weather
	size += sizeof(uint32_t); // base weather

	return size;
}

uint8_t* World::Serialize() const {
	const auto& alloc = this->GetMemoryUsage();
	uint8_t* data{ (uint8_t*)std::malloc(alloc) };
	BinaryWriter buffer{ alloc };

	std::memset(buffer.Get(), 0, alloc);
	buffer.Write<uint16_t>(0xF);
	buffer.Write<uint32_t>(0);
	buffer.Write(m_name, sizeof(uint16_t));
	buffer.Write<uint32_t>(m_width);
	buffer.Write<uint32_t>(m_height);
	buffer.Write<uint32_t>(static_cast<uint32_t>(m_tiles.size()));
	buffer.Write<uint8_t>(0); // unk 1
	buffer.Write<uint16_t>(0); // unk 2
	buffer.Write<uint16_t>(0); // unk 3

	for (auto& tile : m_tiles)
		tile.Serialize(buffer);

	buffer.Write<uint32_t>(0); // unk 4
	buffer.Write<uint32_t>(0); // unk 5
	buffer.Write<uint32_t>(0); // unk 6

	buffer.Write<uint32_t>(0); // weather id
	buffer.Write<uint32_t>(0); // weather on/off status
	buffer.Write<uint32_t>(0); // unk (could be some data related to weather machines with setting like stuff etc.)
	buffer.Write<uint32_t>(0); // unk (could be some data related to weather machines with setting like stuff etc.)

	std::memcpy(data, buffer.Get(), alloc);
	return data;
}
