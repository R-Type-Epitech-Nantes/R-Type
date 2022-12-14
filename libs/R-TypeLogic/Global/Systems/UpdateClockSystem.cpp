/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UpdateClockSystem
*/

#include "UpdateClockSystem.hpp"
#include <chrono>
#include <mutex>
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Server/Components/AfkFrequencyComponent.hpp"

using namespace ecs;

void UpdateClock::run(World &world)
{
    GameClock &clock = world.getResource<GameClock>();
    auto guard = std::lock_guard(clock);
    std::vector<std::shared_ptr<ecs::Entity>> joinedShoot = world.joinEntities<ShootingFrequency>();
    std::vector<std::shared_ptr<ecs::Entity>> joinedAfk = world.joinEntities<AfkFrequency>();

    clock.resetClock();

    if (clock.getElapsedTime() >= 1)
            clock.resetClock();
    for (auto entityPtr : joinedShoot) {
        auto guard = std::lock_guard(*entityPtr.get());
        updateAFrequencyComponent<ShootingFrequency>(clock, entityPtr);
    }
    for (auto entityPtr : joinedAfk) {
        auto guard = std::lock_guard(*entityPtr.get());
        updateAFrequencyComponent<AfkFrequency>(clock, entityPtr);
    }
}
