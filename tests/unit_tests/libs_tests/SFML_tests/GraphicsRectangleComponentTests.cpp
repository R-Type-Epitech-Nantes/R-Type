/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsRectangleComponentTests
*/

#include <criterion/criterion.h>
#include "GraphicsRectangleComponent.hpp"

using namespace ecs;
using namespace graphicECS::SFML::Components;

Test(GraphicsRectangleComponent, test_create_class)
{
    GraphicsRectangleComponent a(100, 100, 10, 10);

    cr_assert_eq(a.shape.getPosition(), sf::Vector2f(100, 100));
    cr_assert_eq(a.shape.getSize(), sf::Vector2f(10, 10));
}