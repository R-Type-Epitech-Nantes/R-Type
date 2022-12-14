/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToServer
*/

#include "SendToServer.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/ControlableComponent.hpp"

void SendToServer::runSystem(ecs::World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> servers = world.joinEntities<ecs::NetworkServer>();
    std::vector<std::shared_ptr<ecs::Entity>> players = world.joinEntities<ecs::Controlable>();
    std::vector<unsigned short> serverIdList;

    auto addToServerList = [&serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        serverIdList.emplace_back(entityPtr->getComponent<ecs::NetworkServer>().id);
    };

    auto update = [this, &world, &serverIdList](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        if (entityPtr->contains<ecs::Networkable>()) {
            unsigned short networkId = entityPtr->getComponent<ecs::Networkable>().id;
            sendToServer<ecs::Velocity, ecs::Position>(world, networkId, entityPtr, serverIdList);
        }
        return;
    };

    std::for_each(servers.begin(), servers.end(), addToServerList);
    if (!serverIdList.empty()) {
        std::for_each(players.begin(), players.end(), update);
    }
}
