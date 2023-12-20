#include <World/Tile.hpp>
#include <Logger/Logger.hpp>

Tile::Tile() : m_position {}, m_foreground_id { 0 }, m_background_id { 0 }, m_parent{ 0 }, m_flags { 0 }, TileExtra { } {
}

bool Tile::IsFlagOn(const eTileFlags& bits) const {
	if (m_flags & bits) {
		return true;
	}
	return false;
}

void Tile::SetFlag(const eTileFlags& bits) {
	m_flags |= bits;
}

void Tile::UnsetFlag(const eTileFlags& bits) {
	m_flags &= ~bits;
}

size_t Tile::GetMemoryUsage() const {
	std::size_t result_size = sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint16_t);
	if (IsFlagOn(TILEFLAG_TILEEXTRA)) {
		result_size += TileExtra::GetMemoryUsage();
	}
	return result_size; // 4 uint16_t (m_foreground, m_background, m_parent, m_flags)
}

void Tile::Serialize(BinaryWriter& writer) const {
	writer.Write<uint16_t>(m_foreground_id);
	writer.Write<uint16_t>(m_background_id);
	writer.Write<uint16_t>(m_parent);
	writer.Write<uint16_t>(m_flags);

	if (IsFlagOn(TILEFLAG_TILEEXTRA)) {
		TileExtra::Serialize(writer);
	}
}
