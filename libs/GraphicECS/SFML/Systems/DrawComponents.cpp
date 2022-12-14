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
#include "GraphicECS/SFML/Components/ChatMessageComponent.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"
#include "GraphicECS/SFML/Resources/GraphicsFontResource.hpp"
#include "GraphicsRectangleComponent.hpp"
#include "GraphicsTextComponent.hpp"
#include "GraphicsTextureResource.hpp"
#include "TextureName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/ActionName.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/Components/DisplayState.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileType.hpp"
#include "R-TypeLogic/Global/Components/InvisibleComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/TextComponent.hpp"

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
    std::string &text = buttonPtr->getComponent<TextComponent>().text;

    if (buttonPtr->contains<GraphicsTextComponent>())
        return;
    buttonPtr->addComponent<GraphicsTextComponent>(newFont, text, pos.x + 10, pos.y + size.y * 0.3);
}

void DrawComponents::addWritableText(std::shared_ptr<Entity> writablePtr, const sf::Font &newFont)
{
    Position &pos = writablePtr->getComponent<Position>();
    Size &size = writablePtr->getComponent<Size>();

    if (writablePtr->contains<GraphicsTextComponent>())
        return;
    writablePtr->addComponent<GraphicsTextComponent>(newFont, writablePtr->getComponent<WritableContent>().content,
        pos.x + size.x * 0.05, pos.y + size.y * 0.2, size.y * 0.4);
}

void DrawComponents::addChatMessageText(std::shared_ptr<Entity> chatMessagePtr, const sf::Font &newFont)
{
    Position &pos = chatMessagePtr->getComponent<Position>();
    Size &size = chatMessagePtr->getComponent<Size>();

    if (chatMessagePtr->contains<GraphicsTextComponent>())
        return;
    chatMessagePtr->addComponent<GraphicsTextComponent>(newFont,
        chatMessagePtr->getComponent<ChatMessage>().author + std::string(" : ")
            + chatMessagePtr->getComponent<ChatMessage>().message,
        pos.x + size.x * 0.05, pos.y + size.y * 0.2, size.y * 0.4);
}

void DrawComponents::addText(std::shared_ptr<Entity> textPtr, const sf::Font &newFont)
{
    Position &pos = textPtr->getComponent<Position>();
    Size &size = textPtr->getComponent<Size>();

    if (textPtr->contains<GraphicsTextComponent>())
        return;
    textPtr->addComponent<GraphicsTextComponent>(
        newFont, textPtr->getComponent<TextComponent>().text, pos.x, pos.y, size.x);
}

void DrawComponents::_updatePlayer(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr, const sf::Font &newFont)
{
    if (layerType.layer == LayerLvL::layer_e::PLAYER) {
        Position &pos = entityPtr->getComponent<Position>();
        Size &size = entityPtr->getComponent<Size>();

        if (!entityPtr->contains<Player>())
            return;
        entityPtr->addComponent<AnimationComponent>();
        entityPtr->addComponent<AnimationFrequencyComponent>(0.05);
        entityPtr->getComponent<AnimationComponent>().currentTexturePos = 0;
        entityPtr->addComponent<GraphicsTextComponent>(
            newFont, entityPtr->getComponent<Player>().name, pos.x + size.x * 0.4, pos.y - 20, size.x * 0.2);
        switch (entityPtr->getComponent<Player>().playerIdentifier % 4) {
            case 0:
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::BLUE_PLAYER_STATIC_1);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::BLUE_PLAYER_STATIC_2);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::BLUE_PLAYER_STATIC_3);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::BLUE_PLAYER_STATIC_4);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::BLUE_PLAYER_STATIC_5);
                break;
            case 1:
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::GREEN_PLAYER_STATIC_1);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::GREEN_PLAYER_STATIC_2);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::GREEN_PLAYER_STATIC_3);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::GREEN_PLAYER_STATIC_4);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::GREEN_PLAYER_STATIC_5);
                break;
            case 2:
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::PINK_PLAYER_STATIC_1);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::PINK_PLAYER_STATIC_2);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::PINK_PLAYER_STATIC_3);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::PINK_PLAYER_STATIC_4);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::PINK_PLAYER_STATIC_5);
                break;
            case 3:
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::YELLOW_PLAYER_STATIC_1);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::YELLOW_PLAYER_STATIC_2);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::YELLOW_PLAYER_STATIC_3);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::YELLOW_PLAYER_STATIC_4);
                entityPtr->getComponent<AnimationComponent>().textures.push_back(
                    GraphicsTextureResource::YELLOW_PLAYER_STATIC_5);
                break;
            default:
                break;
                entityPtr->addComponent<GraphicsTextComponent>(
                    newFont, entityPtr->getComponent<Player>().name, pos.x + size.x * 0.5, pos.y, size.x * 0.2);
        }
    }
}

void DrawComponents::_updateEnemy(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr)
{
    if (layerType.layer == LayerLvL::layer_e::ENEMY) {
        switch (entityPtr->getComponent<Enemy>().enemyType) {
            case Enemy::FIRE: entityPtr->addComponent<TextureName>(GraphicsTextureResource::FIRE_ENEMY); break;
            case Enemy::ELECTRIC: entityPtr->addComponent<TextureName>(GraphicsTextureResource::ELECTRIC_ENEMY); break;
            case Enemy::ICE: entityPtr->addComponent<TextureName>(GraphicsTextureResource::ICE_ENEMY); break;
            case Enemy::BOSS: entityPtr->addComponent<TextureName>(GraphicsTextureResource::BOSS); break;
            default: entityPtr->addComponent<TextureName>(GraphicsTextureResource::BASIC_ENEMY); break;
        };
    }
}

void DrawComponents::_udpateProjectile(LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr)
{
    if (layerType.layer == LayerLvL::layer_e::PROJECTILE) {
        if (entityPtr->contains<EnemyProjectile>()) {
            switch (entityPtr->getComponent<EnemyProjectileType>().parentType) {
                case Enemy::FIRE:
                    entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ENEMY_FIRE);
                    break;
                case Enemy::ELECTRIC:
                    entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ENEMY_ELECTRIC);
                    break;
                case Enemy::ICE:
                    entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ENEMY_ICE);
                    break;
                default: entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ENEMY_BASIC); break;
            };
        }
        if (entityPtr->contains<AlliedProjectile>()) {
            entityPtr->addComponent<TextureName>(GraphicsTextureResource::PROJECTILE_ALLY);
        }
    }
}

void DrawComponents::_updateButton(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr)
{
    if (layerType.layer == LayerLvL::BUTTON) {
        entityPtr->addComponent<TextureName>(GraphicsTextureResource::BUTTON);
        addButtonText(entityPtr, world.getResource<GraphicsFontResource>().font);
    }
    if (layerType.layer == LayerLvL::WRITABLE_BUTTON) {
        entityPtr->addComponent<TextureName>(GraphicsTextureResource::WRITABLE_BUTTON);
    }
}

void DrawComponents::_updateWritable(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr)
{
    if (layerType.layer == LayerLvL::WRITABLE) {
        entityPtr->addComponent<TextureName>(GraphicsTextureResource::WRITABLE);
        addWritableText(entityPtr, world.getResource<GraphicsFontResource>().font);
    }
}

void DrawComponents::_updateText(World &world, LayerLvL &layerType, std::shared_ptr<ecs::Entity> entityPtr)
{
    if (layerType.layer == LayerLvL::CHAT_MESSAGE) {
        entityPtr->removeComponent<GraphicsRectangleComponent>();
        addChatMessageText(entityPtr, world.getResource<GraphicsFontResource>().font);
    }
    if (layerType.layer == LayerLvL::TEXT) {
        entityPtr->removeComponent<GraphicsRectangleComponent>();
        addText(entityPtr, world.getResource<GraphicsFontResource>().font);
    }
}

void DrawComponents::_updateEntities(World &world, std::shared_ptr<ecs::Entity> entityPtr)
{
    auto layerType = entityPtr->getComponent<LayerLvL>();
    if (layerType.layer == LayerLvL::layer_e::OBSTACLE || layerType.layer == LayerLvL::layer_e::ENEMY
        || layerType.layer == LayerLvL::layer_e::PLAYER || layerType.layer == LayerLvL::layer_e::PROJECTILE
        || layerType.layer == LayerLvL::BUTTON || layerType.layer == LayerLvL::WRITABLE
        || layerType.layer == LayerLvL::WRITABLE_BUTTON || layerType.layer == LayerLvL::CHAT_MESSAGE
        || layerType.layer == LayerLvL::TEXT) {
        auto entityPos = entityPtr->getComponent<Position>();
        auto entitySize = entityPtr->getComponent<Size>();

        entityPtr->addComponent<GraphicsRectangleComponent>(entityPos.x, entityPos.y, entitySize.x, entitySize.y);
        _updatePlayer(layerType, entityPtr, world.getResource<GraphicsFontResource>().font);
        _updateEnemy(layerType, entityPtr);
        _udpateProjectile(layerType, entityPtr);
        _updateButton(world, layerType, entityPtr);
        _updateWritable(world, layerType, entityPtr);
        _updateText(world, layerType, entityPtr);
    }
}

void DrawComponents::_updateTexture(World &world, std::shared_ptr<ecs::Entity> entityPtr)
{
    if (world.containsResource<GraphicsTextureResource>()) {
        GraphicsTextureResource &textureResource = world.getResource<GraphicsTextureResource>();
        auto guard = std::lock_guard(textureResource);
        if (entityPtr->contains<TextureName>()) {
            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                textureResource._texturesList[entityPtr->getComponent<TextureName>().textureName].get());
        } else if (entityPtr->contains<AnimationComponent>()) {
            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setTexture(
                textureResource
                    ._texturesList[entityPtr->getComponent<AnimationComponent>()
                                       .textures[entityPtr->getComponent<AnimationComponent>().currentTexturePos]]
                    .get());
        }
        if (entityPtr->contains<Size>())
            entityPtr->getComponent<GraphicsRectangleComponent>().shape.setSize(
                sf::Vector2f(entityPtr->getComponent<Size>().x, entityPtr->getComponent<Size>().y));
    } else {
        entityPtr->getComponent<GraphicsRectangleComponent>().shape.setFillColor(sf::Color::White);
    }
}

void DrawComponents::_drawRectangle(World &world, std::shared_ptr<ecs::Entity> entityPtr,
    graphicECS::SFML::Resources::RenderWindowResource &windowResource)
{
    if (entityPtr->contains<GraphicsRectangleComponent>() && !(entityPtr->contains<Invisible>())) {
        _updateTexture(world, entityPtr);
        if ((entityPtr->getComponent<LayerLvL>().layer == LayerLvL::BUTTON
                || entityPtr->getComponent<LayerLvL>().layer == LayerLvL::WRITABLE
                || entityPtr->getComponent<LayerLvL>().layer == LayerLvL::WRITABLE_BUTTON)
            && world.getResource<MenuStates>().currentState == entityPtr->getComponent<DisplayState>().displayState) {
            windowResource.window.draw(entityPtr->getComponent<GraphicsRectangleComponent>().shape);
        } else if (entityPtr->getComponent<LayerLvL>().layer != LayerLvL::BUTTON
            && entityPtr->getComponent<LayerLvL>().layer != LayerLvL::WRITABLE
            && entityPtr->getComponent<LayerLvL>().layer != LayerLvL::WRITABLE_BUTTON) {
            windowResource.window.draw(entityPtr->getComponent<GraphicsRectangleComponent>().shape);
        }
    }
}

void DrawComponents::_drawText(World &world, std::shared_ptr<ecs::Entity> entityPtr,
    graphicECS::SFML::Resources::RenderWindowResource &windowResource)
{
    if (entityPtr->contains<GraphicsTextComponent>()) {
        if (entityPtr->contains<DisplayState>()
            && world.getResource<MenuStates>().currentState == entityPtr->getComponent<DisplayState>().displayState) {
            windowResource.window.draw(entityPtr->getComponent<GraphicsTextComponent>().text);
        }
        if (entityPtr->contains<Player>() || entityPtr->contains<ChatMessage>()) {
            windowResource.window.draw(entityPtr->getComponent<GraphicsTextComponent>().text);
        }
    }
}

void DrawComponents::_drawComponent(
    World &world, std::shared_ptr<ecs::Entity> entityPtr, RenderWindowResource &windowResource)
{
    auto entityGuard = std::lock_guard(*entityPtr.get());

    if (entityPtr->contains<GraphicsRectangleComponent>() || entityPtr->contains<GraphicsTextComponent>()) {
        _drawRectangle(world, entityPtr, windowResource);
        _drawText(world, entityPtr, windowResource);
    } else {
        _updateEntities(world, entityPtr);
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
        for (auto entityPtr : Inputs) {
            _drawComponent(world, entityPtr, windowResource);
        }
        windowResource.window.display();
    }
}
