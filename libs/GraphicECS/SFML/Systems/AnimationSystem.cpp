/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"
#include "GraphicsRectangleComponent.hpp"
// #include "AnimationDelayComponent.hpp"
#include "AnimationComponent.hpp"
#include "GraphicsTextureResource.hpp"

using namespace ecs;

void AnimationSystem::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> shapes = world.joinEntities<GraphicsRectangleComponent, AnimationComponent/*, AnimationDelayComponent*/>();

    auto shape = [&world](std::shared_ptr<Entity> entity) {
        using texturesNamesVector = std::vector<ecs::GraphicsTextureResource::textureName_e>;
        using texturesMap = std::unordered_map<ecs::GraphicsTextureResource::textureName_e, std::shared_ptr<sf::Texture>>;

        texturesNamesVector texturesNames = entity->getComponent<AnimationComponent>().textures;
        std::size_t currentTexture = entity->getComponent<AnimationComponent>().currentTexture;
        texturesMap textures = world.getResource<GraphicsTextureResource>()._texturesList;

        entity->getComponent<GraphicsRectangleComponent>().shape.setTexture(textures.at(currentTexture).get());
    };
    std::for_each(shapes.begin(), shapes.end(), shape);
}