/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemy
*/

#ifndef CREATEENEMY_HPP_
#define CREATEENEMY_HPP_

#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/Global/Components/CollidableComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/DestinationComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ShootingFrequencyComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

#define MINIMUM_WIDTH  1400
#define MAXIMUM_WIDTH  1700
#define MINIMUM_HEIGTH 0
#define MAXIMUM_HEIGTH 600

namespace ecs
{
    /// @brief This function creates a new Enemy Entity with these parameters
    /// @param world The world in which the Enemy must be created
    /// @param posX Position x of the Enemy
    /// @param posY Position y of the Enemy
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
    /// @param weight Weight of the Enemy
    /// @param sizeX Size x of the Enemy
    /// @param sizeY Size y of the Enemy
    /// @param life Life of the Enemy
    /// @param damage Damage of projectiles fired by this Enemy
    /// @param damageRadius DamageRadius of projectiles fired by this Enemy
    /// @param type the type of the enemy, influencing projectiles and patterns
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Enemy in std::size_t
    std::size_t createNewEnemy(World &world, const int posX, const int posY, const double multiplierAbscissa,
        const double multiplierOrdinate, const short weight, const int sizeX, const int sizeY,
        const unsigned short life, const unsigned short damage, const unsigned short damageRadius,
        unsigned short type, const std::string uuid = "", const unsigned short networkId = 0);

    /// @brief This function creates a new Enemy Entity with random position and with these parameters
    /// @param world The world in which the Enemy must be created
    /// @param multiplierAbscissa The Velocity multiplierAbscissa for the new Enemy
    /// @param multiplierOrdinate The Velocity multiplierOrdinate for the new Enemy
    /// @param weight Weight of the Enemy
    /// @param sizeX Size x of the Enemy
    /// @param sizeY Size y of the Enemy
    /// @param life Life of the Enemy
    /// @param damage Damage of projectiles fired by this Enemy
    /// @param damageRadius DamageRadius of projectiles fired by this Enemy
    /// @param type the type of the enemy, influencing projectiles and patterns
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return Id of the new Enemy in std::size_t
    std::size_t createNewEnemyRandom(World &world, const double multiplierAbscissa, const double multiplierOrdinate,
        const short weight, const int sizeX, const int sizeY, const unsigned short life, const unsigned short damage,
        const unsigned short damageRadius, unsigned short type, const std::string uuid = "",
        const unsigned short networkId = 0);

    /// @brief This function creates a basic enemy with corresponding caracteristics
    /// @param world the world where the enemy will be created
    /// @param networkdId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    std::size_t createBasicEnemy(World &world, const unsigned short networkId = 0);

    /// @brief This function creates a fire enemy with corresponding caracteristics
    /// @param world the world where the enemy will be created
    /// @param networkdId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    std::size_t createFireEnemy(World &world, const unsigned short networkId = 0);

    /// @brief This function creates an electric enemy with corresponding caracteristics
    /// @param world the world where the enemy will be created
    /// @param networkdId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    std::size_t createElectricEnemy(World &world, const unsigned short networkId = 0);

    /// @brief This function creates an ice enemy with corresponding caracteristics
    /// @param world the world where the enemy will be created
    /// @param networkdId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    std::size_t createIceEnemy(World &world, const unsigned short networkId = 0);

    /// @brief This function creates a boss with corresponding caracteristics, more life, more damage, more everything...
    /// @param world the world where the boss will be created
    /// @param networkdId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    std::size_t createBoss(World &world, const unsigned short networkId = 0);

    /// @brief This function creates a boss pawn with corresponding caracteristics, everything is reduced except the projectiles
    /// @param world the world where the pawn will be created
    /// @param pos the boss pos, to decide where to spawn the pawn
    /// @param pawnType the type of the generated pawn (between BASIC and ELECTRIC)
    /// @param networkdId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    std::size_t createBossPawn(World &world, Position &pos, unsigned int pawnType, const unsigned short networkId = 0);

} // namespace ecs
#endif /* !CREATEENEMY_HPP_ */
