/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateProjectile
*/

#ifndef CREATEPROJECTILE_HPP_
#define CREATEPROJECTILE_HPP_

#include "GameComponents/CollidableComponent.hpp"
#include "GameComponents/DamageComponent.hpp"
#include "GameComponents/DamageRadiusComponent.hpp"
#include "GameComponents/LifeComponent.hpp"
#include "GameComponents/LifeTimeComponent.hpp"
#include "GameComponents/NewlyCreated.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameComponents/ProjectileComponent.hpp"
#include "GameComponents/SizeComponent.hpp"
#include "GameComponents/VelocityComponent.hpp"
#include "GameComponents/WeightComponent.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "GameSharedResources/Random.hpp"
#include "World/World.hpp"
#include "SFMLComponents/LayerLvL.hpp"

namespace ecs
{
    /// @brief This function can create a new Projectile Entity in the world passed as params
    /// @param world The world in which the Projectile must be created
    /// @param posX The start position x of the new Projectile
    /// @param posY The start position y of the new Projectile
    /// @param multiplierAbscissa The Velocity multiplierAbscissa of the new Projectile
    /// @param multiplierOrdinate The Velocity multiplierOrdinate of the new Projectile
    /// @param damage The Damage of the new Projectile
    /// @param uuid The uuid of the entity. Can be empty.
    /// @param networkId The id of the Networkable Component. In the client instance, it MUST NOT be filled in.
    /// @return  Id of the new Projectile in std::size_t
    inline std::size_t createNewProjectile(World &world, const int posX, const int posY,
        const double multiplierAbscissa, const double multiplierOrdinate, const unsigned short damage,
        const std::string uuid = "", unsigned short networkId = 0)
    {
        Entity &entity = world.addEntity()
                             .addComponent<Position>(posX, posY)
                             .addComponent<Weight>(1)
                             .addComponent<Size>(2, 1)
                             .addComponent<LifeTime>(100.0)
                             .addComponent<Life>(10)
                             .addComponent<Damage>(damage)
                             .addComponent<DamageRadius>(5)
                             .addComponent<Collidable>()
                             .addComponent<Projectile>()
                             .addComponent<Velocity>(multiplierAbscissa, multiplierOrdinate);

        if (networkId) {
            // Case : Creation in a server instance
            entity.addComponent<NewlyCreated>(uuid, false);
            entity.addComponent<Networkable>(networkId);
        } else {
            // Case : Creation in a Client instance
            if (uuid != "") {
                // Special case : the client created the entity and not the server
                entity.addComponent<NewlyCreated>(uuid, true);
            }
            entity.addComponent<LayerLvL>(LayerLvL::layer_e::PROJECTILE);
        }
        return entity.getId();
    }
} // namespace ecs
#endif /* !CREATEPROJECTILE_HPP_ */
