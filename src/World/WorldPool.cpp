#include <World/WorldPool.hpp>

WorldPool g_worldPool;
WorldPool* GetWorldPool() {
    return &g_worldPool;
}

WorldPool::~WorldPool() {
    /*for (auto& [name, world] : this->m_worlds)
        this->RemoveWorld(name);*/
    m_worlds.clear();
}

void WorldPool::SendWorldOffer(Player* player) {
    WorldMenu menu {};
    menu.SetDefault("START")
        ->AddFilter()
        ->SetMaxRows(2)
        ->AddHeading("Active Worlds")
        ->AddFloater("START", 0, 0.7, Color{ 0xB4, 0xBD, 0xC2 });
    VarList::OnRequestWorldSelectMenu(player->Get(), menu.Get());
}

std::shared_ptr<World> WorldPool::NewWorld(std::string name) {
    m_worlds[name] = std::make_shared<World>(name, 100, 60);
    m_worlds[name]->Generate();
    return m_worlds[name];
}

void WorldPool::RemoveWorld(std::string name) {
    m_worlds[name].reset();
    m_worlds.erase(name);
}

std::shared_ptr<World> WorldPool::GetWorld(std::string name) {
    for (auto& world : m_worlds) {
        if (world.first == name) {
            return world.second;
        }
    }
    return nullptr;
}

std::unordered_map<std::string, std::shared_ptr<World>> WorldPool::GetWorlds() {
    return m_worlds;
}
size_t WorldPool::GetActiveWorlds() const {
    size_t active_worlds = 0;
    for (auto& world : m_worlds) {
        if (world.second->GetPlayers().size() > 0) {
            active_worlds++;
		}
    }
    return active_worlds;
}