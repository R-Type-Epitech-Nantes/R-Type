/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Death_LifeTime_System_tests
*/

#include <criterion/criterion.h>
#include "Entity/Entity.hpp"
#include "World/World.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateProjectile.hpp"
#include "R-TypeLogic/Global/Components/DeathComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeTimeComponent.hpp"
#include "R-TypeLogic/Global/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/Server/Systems/LifeTimeDeathSystem.hpp"

using namespace ecs;

Test(add_Death_component_system, lifeTime_death_entity)
{
    World world(1);

    std::chrono::duration<double> time_1(1.0);
    std::chrono::duration<double> time_0(0.0);

    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.getEntity(1).getComponent<LifeTime>().timeLeft = time_0;

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

    world.addSystem<LifeTimeDeath>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Death>();

    cr_assert_eq(0, joined.size());
    cr_assert_eq(1, death_joined.size());
}

Test(add_Death_component_system, lifeTime_death_entities)
{
    World world(1);

    std::chrono::duration<double> time_1(1.0);
    std::chrono::duration<double> time_0(0.0);

    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);
    createNewProjectile(world, 10, 10, 1, 1, 10);

    world.getEntity(1).getComponent<LifeTime>().timeLeft = time_1;
    world.getEntity(2).getComponent<LifeTime>().timeLeft = time_0;
    world.getEntity(3).getComponent<LifeTime>().timeLeft = time_0;

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

    world.addSystem<LifeTimeDeath>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Death>();

    cr_assert_eq(0, joined.size());
    cr_assert_eq(2, death_joined.size());
}

Test(add_Death_component_system, none_entities_lifeTime_death_entities)
{
    World world(1);

    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<Death>();

    world.addSystem<LifeTimeDeath>();

    world.runSystems();

    std::vector<std::shared_ptr<ecs::Entity>> death_joined = world.joinEntities<Death>();

    cr_assert_eq(0, joined.size());
    cr_assert_eq(0, death_joined.size());
}
