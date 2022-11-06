/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DeathLifeSystem
*/

#ifndef DEATHLIFESYSTEM_HPP_
#define DEATHLIFESYSTEM_HPP_

#include <mutex>
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameLevel.hpp"

namespace ecs
{
    /// @brief This is the DeathLife System.
    /// This System takes all entities that have a Life Component with 0 HP/life or less and adds a Death Component to
    /// them. It's a system that will be called by the engine world with the function runSystem()
    struct DeathLife : public System {
        inline void run(World &world) override final
        {
            std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Life>();

            auto deathlifetime = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
                auto guard = std::lock_guard(*entityPtr.get());
                if (entityPtr.get()->getComponent<Life>().lifePoint <= 0) {
                    if (entityPtr->contains<Player>()) {
                        Client client = world.getTransisthorBridge()->getCommunicatorInstance().getClientByHisId(
                            entityPtr->getComponent<NetworkClient>().id);

                        world.getTransisthorBridge()->getCommunicatorInstance().sendDataToAClient(
                            client, nullptr, 0, 13);
                        entityPtr->getComponent<Life>().lifePoint = 1000;
                    } else {
                        if (entityPtr->contains<Enemy>()) {
                            GameLevel &gameLevel = world.getResource<GameLevel>();
                            gameLevel.lock();
                            gameLevel.addNewKills();
                            gameLevel.unlock();
                        }
                        entityPtr.get()->addComponent<Death>();
                    }
                }
            };
            std::for_each(joined.begin(), joined.end(), deathlifetime);
        }
    };
} // namespace ecs

#endif /* !DEATHLIFESYSTEM_HPP_ */
