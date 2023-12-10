#pragma once
#include <vector>
#include <memory>
#include <Utils/MiscUtils.hpp>
#include <Utils/BinaryWriter.hpp>
#include <Logger/Logger.hpp>
#include <string>
#include <fmt/core.h>

class PlayerTributeManager {
public:
    void Build();
    void Kill();

    uint32_t GetSize() { return (uint32_t)m_size; };
    uint8_t* GetData() { return reinterpret_cast<uint8_t*>(m_data); };

    uint32_t GetHash() { return m_hash; };
public:
    PlayerTributeManager() = default;
    ~PlayerTributeManager() = default;
private:
	size_t m_size;
	char* m_data;
    uint32_t m_hash;
};

PlayerTributeManager* GetPlayerTributeManager();