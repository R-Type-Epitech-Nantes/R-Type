/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DrawComponents
*/

#include "DrawComponents.hpp"
#include <algorithm>
#include <mutex>
#include "AnimationComponent.hpp"
#include "AnimationFrequencyComponent.hpp"
#include "GraphicECS/SFML/Resources/GraphicsFontResource.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextComponent.hpp"
#include "GraphicsTextureResource.hpp"
#include "TextureName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Components;

bool DrawComponents::compareLayer(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
    return (e1->getComponent<LayerLvL>().layer < e2->getComponent<LayerLvL>().layer);
}

void DrawComponents::addButtonText(std::shared_ptr<Entity> buttonPtr, const sf::Font &newFont)
{
    Position &pos = buttonPtr->getComponent<Position>();
    Size &size = buttonPtr->getComponent<Size>();

    if (buttonPtr->contains<GraphicsTextComponent>())
        return;
    switch (buttonPtr->getComponent<ActionName>().actionName) {
        case ButtonActionMap::RESUME:
            buttonPtr->addComponent<GraphicsTextComponent>(
                newFont, "Resume", pos.x, pos.y + size.y * 0.5, size.x * 0.3);
            break;
        case ButtonActionMap::EXIT:
            buttonPtr->addComponent<GraphicsTextComponent>(
                newFont, "Exit the game", pos.x, pos.y + size.y * 0.5, size.x * 0.3);
            break;
        case ButtonActionMap::PAUSE:
            buttonPtr->addComponent<GraphicsTextComponent>(newFont, "Pause", pos.x, pos.y + size.y * 0.5, size.x * 0.3);
            break;
        default: break;
    }
}

void DrawComponents::run(World &world)
{
    std::vector<std::shared_ptr<Entity>> Inputs = world.joinEntities<LayerLvL>();
    RenderWindowResource &windowResource = world.getResource<RenderWindowResource>();
    auto guard = std::lock_guard(windowResource);

    if (windowResource.window.isOpen()) {
        windowResource.window.clear(sf::Color(0x151123));
        std::sort(Inputs.begin(), Inputs.end(), compareLayer);
        auto layer = [&world, &windowResource](std::shared_ptr<Entity> entityPtr) {
            std::lock_guard(*entityPtr.get());
            if (entityPtr->contains<GraphicsRectangleComponent>() || entityPtr->contains<GraphicsTextComponent>()) {
                if (entityPtr->contains<GraphicsRectangleComponent>()) {
                    if (world.containsResource<GraphicsTextureResource>()) {
                        GraphicsTextureResource &textureResource = world.getResource<GraphicsTextureResource>();
                        auto guard = std::lock_guard(textureResource);
                        if (entityPtr->contains<TextureName>()) {
                            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                                textureResource._texturesList[entityPtr->getComponent<TextureName>().textureName]
                                    .get());
                        } else if (entityPtr->contains<AnimationComponent>()) {
                            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                                textureResource
                                    ._texturesList[entityPtr->getComponent<AnimationComponent>()
                                                       .textures[entityPtr->getComponent<AnimationComponent>()
                                                                     .currentTexturePos]]
                                    .get());
                        }
                    } else {
                        entityPtr->getComponent<GraphicsRectangleComponent>().shape.setFillColor(sf::Color::White);
                    }
                    if (entityPtr->getComponent<LayerLvL>().layer == LayerLvL::BUTTON
                        && world.getResource<MenuStates>().currentState
                            == entityPtr->getComponent<DisplayState>().displayState) {
                        windowResource.window.draw(entityPtr->getComponent<GraphicsRectangleComponent>().shape);
                    } else if (entityPtr->getComponent<LayerLvL>().layer != LayerLvL::BUTTON) {
                        windowResource.window.draw(entityPtr->getComponent<GraphicsRectangleComponent>().shape);
                    }
                }
                if (entityPtr->contains<GraphicsTextComponent>()) {
                    if (world.getResource<MenuStates>().currentState
                        == entityPtr->getComponent<DisplayState>().displayState) {
                        windowResource.window.draw(entityPtr->getComponent<GraphicsTextComponent>().text);
                    }
                }
                return;
            }
            auto layerType = entityPtr->getComponent<LayerLvL>();
            if (layerType.layer == LayerLvL::layer_e::OBSTACLE || layerType.layer == LayerLvL::layer_e::ENEMY
                || layerType.layer == LayerLvL::layer_e::PLAYER || layerType.layer == LayerLvL::layer_e::PROJECTILE
                || layerType.layer == LayerLvL::BUTTON) {
                auto entityPos = entityPtr->getComponent<Position>();
                auto entitySize = entityPtr->getComponent<Size>();

                entityPtr->addComponent<GraphicsRectangleComponent>(
                    entityPos.x, entityPos.y, entitySize.x, entitySize.y);
                if (layerType.layer == LayerLvL::layer_e::PLAYER) {
                    entityPtr->addComponent<AnimationComponent>();
                    entityPtr->addComponent<AnimationFrequencyComponent>(0.05);
                    entityPtr->getComponent<AnimationComponent>().currentTexturePos = 0;
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_1);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_2);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_3);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_4);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_5);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_6);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_7);
                    entityPtr->getComponent<AnimationComponent>().textures.push_back(
                        GraphicsTextureResource::PLAYER_STATIC_8);
                }
                if (layerType.layer == LayerLvL::layer_e::ENEMY)
                    entityPtr->addComponent<TextureName>(GraphicsTextureResource::ENEMY_STATIC);
                if (layerType.layer == LayerLvL::layer_e::PROJECTILE) {
                    if (entityPtr->contains<EnemyProjectile>()) {
                        entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ENEMY);
                    }
                    if (entityPtr->contains<AlliedProjectile>()) {
                        entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ALLY);
                    }
                }
                if (layerType.layer == LayerLvL::BUTTON) {
                    entityPtr->addComponent<TextureName>(GraphicsTextureResource::BUTTON);
                    addButtonText(entityPtr, world.getResource<GraphicsFontResource>().font);
                }
            }
        };
        std::for_each(Inputs.begin(), Inputs.end(), layer);
        windowResource.window.display();
    }
}
