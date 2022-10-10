/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreatePlayer_test
*/

#include <algorithm>
#include <iostream>
#include <criterion/criterion.h>
#include "World/World.hpp"
#include "CreatePlayer.hpp"

using namespace ecs;

Test(CreatePlayer_test, CreatePlayer)
{
    World world(1);

    std::size_t id_new_entity = createNewPlayer(world, 50, 20, 1, 5, 5, 100, 10, 5);

    cr_assert_eq(1, id_new_entity);
    cr_assert_eq(50, world.getEntity(1).getComponent<Position>().x);
}