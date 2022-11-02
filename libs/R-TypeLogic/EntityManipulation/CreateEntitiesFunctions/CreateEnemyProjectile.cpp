/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateEnemyProjectile
*/

#include "CreateEnemyProjectile.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/EnemyProjectileType.hpp"

namespace ecs
{
    std::size_t createNewEnemyProjectile(
        World &world, std::shared_ptr<ecs::Entity> enemy, const std::string uuid, unsigned short networkId)
    {
        Position pos = enemy.get()->getComponent<Position>();
        Damage damage = enemy.get()->getComponent<Damage>();

        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Position>(pos.x, pos.y + 20)
            .addComponent<Velocity>(-400, 0)
            .addComponent<Weight>(1)
            .addComponent<Size>(40, 40)
            .addComponent<LifeTime>(3)
            .addComponent<Life>(1)
            .addComponent<Damage>(damage)
            .addComponent<DamageRadius>(5)
            .addComponent<Collidable>()
            .addComponent<EnemyProjectile>(enemy.get()->getComponent<Networkable>().id);

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
            entity.addComponent<EnemyProjectileType>(enemy->getComponent<Enemy>().enemyType);
        }
        return entity.getId();
    }
} // namespace ecs
