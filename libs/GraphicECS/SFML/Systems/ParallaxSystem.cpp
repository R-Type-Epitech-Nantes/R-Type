/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ParallaxSystem
*/

#include "ParallaxSystem.hpp"
#include "GraphicECS/SFML/Components/ParallaxComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"

#define MAXIMUM_WIDTH 1920

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

void Parallax::run(World &world)
{
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<ParallaxBackground>();

    auto makeParallax = [](std::shared_ptr<ecs::Entity> entityPtr) {
        auto guard = std::lock_guard(*entityPtr.get());
        Position &pos = entityPtr.get()->getComponent<Position>();

        if (pos.x <= MAXIMUM_WIDTH * -1) {
            pos.x = MAXIMUM_WIDTH;
        }
    };

    std::for_each(joined.begin(), joined.end(), makeParallax);
}
