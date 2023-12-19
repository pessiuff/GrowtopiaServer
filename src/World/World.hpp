#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <World/Tile.hpp>
#include <Player/Player.hpp>
#include <Utils/Math.hpp>
#include <Utils/RandUtils.hpp>
#include <Utils/BinaryWriter.hpp>
#include <Manager/Item/ItemComponent.hpp>
#include <Logger/Logger.hpp>
#include <Manager/Item/ItemType.hpp>
#include <Manager/Item/ItemManager.hpp>

class World {
public:
	explicit World(const std::string& name, const uint32_t& width, const uint32_t& height);
	~World();

	void SetSize(const uint32_t& width, const uint32_t& height) { m_width = width; m_height = height; };
	CL_Vec2<int> GetSize() const { return CL_Vec2<int>(m_width, m_height); };

	void Generate();

	Tile* GetTile(const uint32_t& x, const uint32_t& y);
	Tile* GetTile(const CL_Vec2<int>& pos) { return GetTile(pos); };

	CL_Vec2<int> GetTilePos(const uint16_t& item_id) const;
	CL_Vec2<int> GetTilePos(const eItemTypes& item_type) const;

	uint32_t AddPlayer(Player* player);
	void RemovePlayer(Player* player);
	bool HasPlayer(Player* player);
	std::vector<Player*> GetPlayers();

	void Broadcast(const std::function<void(Player*)>& func);

	std::size_t GetMemoryUsage() const;
	uint8_t* Serialize() const;
private:
	std::string m_name;
	uint32_t m_width, m_height;

	uint32_t m_netID;
	uint32_t m_flags;

	std::vector<Tile> m_tiles;
	std::unordered_map<uint32_t, Player*> m_players;
};