#pragma once

#include <World/TileExtra.hpp>
#include <Utils/Math.hpp>
#include <Utils/BinaryWriter.hpp>
#include <World/WorldEnums.hpp>

class Tile : public TileExtra {
public:
	Tile();
	~Tile() = default;

	void SetPosition(const CL_Vec2<int>& position) { m_position = position; };
	const CL_Vec2<int>& GetPosition() const { return m_position; };

	void SetForeground(const uint16_t& foreground_id) { m_foreground_id = foreground_id; };
	const uint16_t& GetForeground() const { return m_foreground_id; };

	void SetBackground(const uint16_t& background_id) { m_background_id = background_id; };
	const uint16_t& GetBackground() const { return m_background_id; };

	void SetParent(const uint16_t& parent) { m_parent = parent; };
	const uint16_t& GetParent() const { return m_parent; };

	bool IsFlagOn(const eTileFlags& bits) const;
	void SetFlag(const eTileFlags& bits);
	void UnsetFlag(const eTileFlags& bits);

	size_t GetMemoryUsage() const;
	void Serialize(BinaryWriter& writer) const;
private:
	CL_Vec2<int> m_position;
	uint16_t
		m_foreground_id,
		m_background_id,
	    m_parent,
		m_flags;
};
