/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Death_System_tests
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/Global/Systems/DeathSystem.hpp"

using namespace ecs;

Test(Death_system, kill_entity)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Projectile>();

    world.getEntity(1).addComponent<Death>();

    world.addSystem<DeathSystem>();

    world.getEntity(1).getComponent<Death>().modified = false;

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Projectile>();

    cr_assert_eq(1, joined.size());
    cr_assert_eq(0, death_joined.size());
}

Test(Death_system, kill_entities)
{
    World world(1);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Projectile>();

    world.getEntity(2).addComponent<Death>();

    world.addSystem<DeathSystem>();

    world.getEntity(2).getComponent<Death>().modified = false;

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Projectile>();

    cr_assert_eq(3, joined.size());
    cr_assert_eq(2, death_joined.size());
}

Test(Death_system, kill_entities_with_an_Enemy)
{
    World world(1);

    world.addResource<RandomDevice>();

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewEnemy(world, 10, 10, 1, 1, 1, 4, 4, 100, 10, 5, Enemy::BASIC);

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position>();

    world.getEntity(1).addComponent<Death>();
    world.getEntity(3).addComponent<Death>();

    world.getEntity(1).getComponent<Death>().modified = false;
    world.getEntity(3).getComponent<Death>().modified = false;

    world.addSystem<DeathSystem>();
    world.addResource<NetworkableIdGenerator>();
    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> aliveJoined = world.joinEntities<Position>();

    cr_assert_eq(1, aliveJoined.size());
}

Test(Death_system, kill_entities_without_update)
{
    World world(1);

    world.addResource<RandomDevice>();

    createNewEnemy(world, 10, 10, 1, 1, 1, 4, 4, 100, 10, 5, Enemy::BASIC);
    createNewEnemy(world, 10, 10, 1, 1, 1, 4, 4, 100, 10, 5, Enemy::BASIC);
    createNewEnemy(world, 10, 10, 1, 1, 1, 4, 4, 100, 10, 5, Enemy::BASIC);

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Position>();

    world.getEntity(1).addComponent<Death>();

    world.addSystem<DeathSystem>();
    world.addResource<NetworkableIdGenerator>();
    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> allJoined = world.joinEntities<Position>();

    cr_assert_eq(3, joined.size());
    cr_assert_eq(3, allJoined.size());
}