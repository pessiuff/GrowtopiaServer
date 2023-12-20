#include <World/TileExtra.hpp>

std::size_t TileExtra::GetMemoryUsage() const {
	size_t result_size { 1 };

	switch (GetExtraType()) {
	case TYPE_DOOR: {
		const auto& door = Door{ m_doorData };
		result_size += sizeof(uint16_t)
			+ m_doorData.GetLabel().length()
			+ sizeof(uint8_t)
		;
		break;
	}
	default:
		break;
	}
	return result_size;
}

void TileExtra::Serialize(BinaryWriter& writer) const {
	writer.Write<uint8_t>(GetExtraType());

	switch (GetExtraType()) {
	case TYPE_DOOR: {
		const auto& door = Door{ m_doorData };
		writer.Write(door.GetLabel(), sizeof(uint16_t));
		writer.Write<uint8_t>(0);
		break;
	}
	default:
		break;
	}
}

