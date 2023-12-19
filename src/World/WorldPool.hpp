#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <World/World.hpp>
#include <Player/Player.hpp>
#include <Utils/Wrapper/WorldMenu.hpp>
#include <Packet/VariantFunction.hpp>

class WorldPool {
public:
    WorldPool() = default;
    ~WorldPool();

public:
    void SendWorldOffer(Player* player);

    std::shared_ptr<World> NewWorld(std::string name);
    void RemoveWorld(std::string name);
    std::shared_ptr<World> GetWorld(std::string name);

    std::unordered_map<std::string, std::shared_ptr<World>> GetWorlds();
    size_t GetActiveWorlds() const;

private:
    std::unordered_map<std::string, std::shared_ptr<World>> m_worlds{};
};

WorldPool* GetWorldPool();