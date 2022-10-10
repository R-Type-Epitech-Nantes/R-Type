/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateObstacle
*/

#ifndef CREATEOBSTACLE_HPP_
#define CREATEOBSTACLE_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/ObstacleComponent.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "World/World.hpp"

namespace ecs
{

    /// @brief This function can create a new Obstacle Entity in the world pass in params
    /// @param world The world in that the Obstacle must be created
    /// @param pos The position of the new Obstacle
    /// @param damage The damage inflicted to an Entity if this Entity hits this Obstacle
    /// @return Id of the new Obstacle in std::size_t
    inline std::size_t createNewObstacle(World &world, Position &pos, Damage &damage)
    {
        std::size_t new_obstacle = world.addEntity()
                                       .addComponent<Position>(pos.x, pos.y)
                                       .addComponent<Weight>(1)
                                       .addComponent<Size>(1, 1)
                                       .addComponent<Lifetime>()
                                       .addComponent<Life>(10)
                                       .addComponent<Damage>(damage)
                                       .addComponent<DamageRadius>(5)
                                       .addComponent<Collidable>()
                                       .addComponent<Obstacle>()
                                       .getId();
        return new_obstacle;
    }
} // namespace ecs
#endif /* !CREATEOBSTACLE_HPP_ */
