/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendToServer
*/

#pragma once

#include <algorithm>
#include <concepts>
#include <map>
#include <typeindex>
#include "GraphicECS/SFML/Components/InputDelayComponent.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/Controllable.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Components/NetworkServer.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EquipmentComponent.hpp"
#include "R-TypeLogic/Global/Components/InvinsibleComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"

///@brief a static map which is used to know which ID is used for a component type for the RFC protocol
static const std::map<std::type_index, unsigned short> componentRFCId = {{typeid(ecs::Destination), 1},
    {typeid(ecs::Equipment), 2}, {typeid(ecs::Invinsible), 3}, {typeid(ecs::Life), 4}, {typeid(ecs::Position), 5},
    {typeid(ecs::Velocity), 6}, {typeid(ecs::Death), 7}};

struct SendToServer : public ecs::System {
    /// @brief A template function which is used when there is no component to send to the server.
    /// @tparam ...C The component types
    /// @param world The world that the system is running in.
    /// @param networkId The id which is common to the server and the client
    /// @param entity Entity which must be shared
    /// @param serverIdList The list of servers to which the datas must be sent
    template <std::derived_from<ecs::Component>... C>
        requires(sizeof...(C) == 0)
    void sendToServer(ecs::World &world, const unsigned short &networkId, std::shared_ptr<ecs::Entity> entity,
        const std::vector<unsigned short> &serverIdList) const
    {
        (void)networkId;
        (void)entity;
        (void)serverIdList;
        (void)world;
        return;
    }

    /// @brief A template function which is used when there is at least one component to send to the server.
    /// @tparam C1 The first component type
    /// @tparam ...C2 The other component types
    /// @param world The world that the system is running in.
    /// @param networkId The id which is common to the server and the client
    /// @param entity Entity which must be shared
    /// @param serverIdList The list of servers to which the datas must be sent
    template <std::derived_from<ecs::Component> C1, std::derived_from<ecs::Component>... C2>
    void sendToServer(ecs::World &world, const unsigned short &networkId, std::shared_ptr<ecs::Entity> entity,
        const std::vector<unsigned short> &serverIdList) const
    {
        if (componentRFCId.find(typeid(C1)) != componentRFCId.end()) {
            if (entity->contains<C1>()) {
                C1 &component = entity->getComponent<C1>();
                if (component.modified) {
                    if (entity->contains<graphicECS::SFML::Components::InputDelayComponent>()) {
                        entity->getComponent<ecs::Velocity>().multiplierAbscissa =
                            entity->getComponent<graphicECS::SFML::Components::InputDelayComponent>()
                                .multiplierAbscissa;
                        entity->getComponent<ecs::Velocity>().multiplierOrdinate =
                            entity->getComponent<graphicECS::SFML::Components::InputDelayComponent>()
                                .multiplierOrdinate;
                        entity->removeComponent<graphicECS::SFML::Components::InputDelayComponent>();
                    }
                    component.modified = false;
                    component.sendToEveryone = true;
                    std::free(world.getTransisthorBridge().get()->transitEcsDataToNetworkData<C1>(
                        networkId, componentRFCId.find(typeid(C1))->second, component, serverIdList));
                }
            }
        }
        sendToServer<C2...>(world, networkId, entity, serverIdList);
    }

    /// @brief For each player, send their velocity to the server
    /// @param world The world that the system is running in.
    void runSystem(ecs::World &world);

    /// @brief It runs the system
    /// @param world The world that the system is running in.
    inline void run(ecs::World &world) override final { runSystem(world); }
};
