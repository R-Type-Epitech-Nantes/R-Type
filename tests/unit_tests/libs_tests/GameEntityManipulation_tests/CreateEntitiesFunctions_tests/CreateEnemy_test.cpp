/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateEnemy_test
*/

#include <criterion/criterion.h>
#include "World/World.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateEnemy.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"

using namespace ecs;

Test(CreateEnemy_test, CreateEnemy)
{
    World world(1);

    world.addResource<RandomDevice>();

    std::size_t id_new_entity = createNewEnemy(world, 10, 10, 1, 1, 1, 5, 5, 100, 10, 5, Enemy::BASIC);

    cr_assert_eq(1, id_new_entity);
}
