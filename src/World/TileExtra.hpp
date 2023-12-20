#pragma once
#include <Utils/BinaryWriter.hpp>

class TileExtra {
public:
	TileExtra() : m_doorData() {};
	~TileExtra() = default;

	enum eType : uint8_t {
		TYPE_DEFAULT = 0,
		TYPE_DOOR,
		TYPE_MAIN_DOOR
	};

	struct Door {
		std::string m_label;
		std::string m_unknown;

		void SetLabel(const std::string& label) { m_label = label; }
		std::string GetLabel() const { return m_label; }
	} m_doorData;

	void SetExtraType(eType type) { m_type = type; };
	eType GetExtraType() const { return m_type; };

	std::size_t GetMemoryUsage() const;
	void Serialize(BinaryWriter& writer) const;
private:
	eType m_type;
};
