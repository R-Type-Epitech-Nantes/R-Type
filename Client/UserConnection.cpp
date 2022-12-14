/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UserConnection
*/

#include "UserConnection.hpp"
#include "ButtonAction.hpp"
#include "Error/Error.hpp"
#include "GraphicECS/SFML/Components/ActionQueueComponent.hpp"
#include "GraphicECS/SFML/Components/AllowControllerComponent.hpp"
#include "GraphicECS/SFML/Components/AllowMouseAndKeyboardComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerButtonInputComponent.hpp"
#include "GraphicECS/SFML/Components/ControllerJoystickInputComponent.hpp"
#include "GraphicECS/SFML/Components/KeyboardInputComponent.hpp"
#include "GraphicECS/SFML/Components/MouseInputComponent.hpp"
#include "GraphicECS/SFML/Components/TextureName.hpp"
#include "GraphicECS/SFML/Components/WritableContentComponent.hpp"
#include "GraphicECS/SFML/Resources/GraphicsFontResource.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"
#include "GraphicECS/SFML/Resources/RenderWindowResource.hpp"
#include "GraphicECS/SFML/Systems/AnimationSystem.hpp"
#include "GraphicECS/SFML/Systems/DrawComponents.hpp"
#include "GraphicECS/SFML/Systems/InputManagement.hpp"
#include "GraphicECS/SFML/Systems/MusicManagement.hpp"
#include "GraphicECS/SFML/Systems/ParallaxSystem.hpp"
#include "GraphicECS/SFML/Systems/SfObjectFollowEntitySystem.hpp"
#include "GraphicECS/SFML/Systems/SoundManagement.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/TransisthorECSLogic/Client/Systems/SendToServer.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/ButtonActionMap.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/GameStates.hpp"
#include "R-TypeLogic/EntityManipulation/ButtonManipulation/SharedResources/MenuStates.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateButton.hpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateText.cpp"
#include "R-TypeLogic/EntityManipulation/CreateEntitiesFunctions/CreateWritable.hpp"
#include "R-TypeLogic/Global/SharedResources/GameClock.hpp"
#include "R-TypeLogic/Global/SharedResources/Random.hpp"
#include "R-TypeLogic/Global/Systems/DeathSystem.hpp"
#include "R-TypeLogic/Global/Systems/MovementSystem.hpp"
#include "R-TypeLogic/Global/Systems/UpdateClockSystem.hpp"

using namespace client_data;
using namespace graphicECS::SFML::Resources;
using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

UserConnection::UserConnection()
{
    _pseudo = "";
    _password = "";
    _world = std::make_shared<World>(1);
}

UserConnection::~UserConnection() {}

void UserConnection::_loadResourcesUserConnection()
{
    _world->addResource<RandomDevice>()
        .addResource<GameClock>()
        .addResource<GameStates>()
        .addResource<RenderWindowResource>("Login", sf::VideoMode(360, 640, 32))
        .addResource<GraphicsFontResource>(FONT_PATH)
        .addResource<MusicResource>(MusicResource::music_e::LEVEL_ONE_THEME, BACKGROUND_MUSIC_1)
        .addResource<MenuStates>(MenuStates::MAIN_MENU)
        .addResource<ButtonActionMap>(
            ButtonActionMap::WRITABLE_BUTTON, std::function<void(World &, Entity &)>(writableButtonAction))
        .addResource<GraphicsTextureResource>(GraphicsTextureResource::BUTTON, BUTTON_TEXTURE_PATH);
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::WRITABLE, WRITABLE_BUTTON_TEXTURE_PATH);
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::WRITABLE_BUTTON, WRITABLE_BUTTON_TEXTURE_PATH);
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::WRITABLE_SELECTED, WRITABLE_SELECTED_TEXTURE_PATH);
    _world->getResource<ButtonActionMap>().addAction(
        ButtonActionMap::WRITABLE, std::function<void(World &, Entity &)>(selectAWritable));
    _world->getResource<GraphicsTextureResource>().addTexture(
        GraphicsTextureResource::BACKGROUND_LAYER, BASIC_BACKGROUND_PATH, sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
}

void UserConnection::_loadSystemsUserConnection()
{
    _world->addSystem<UpdateClock>()
        .addSystem<DeathSystem>()
        .addSystem<DrawComponents>()
        .addSystem<InputManagement>()
        .addSystem<SendToServer>()
        .addSystem<SendNewlyCreatedToServer>()
        .addSystem<SfObjectFollowEntitySystem>()
        .addSystem<Parallax>()
        .addSystem<Movement>()
        .addSystem<AnimationSystem>()
        .addSystem<MusicManagement>()
        .addSystem<SoundManagement>();
}

void UserConnection::_setInputUserConnection(ecs::Entity &entity)
{
    entity.getComponent<MouseInputComponent>().MouseMapActions.emplace(
        std::make_pair<sf::Mouse::Button, std::pair<ActionQueueComponent::inputAction_e, float>>(
            sf::Mouse::Button::Left,
            std::make_pair<ActionQueueComponent::inputAction_e, float>(ActionQueueComponent::BUTTON_CLICK, 0)));
}

void UserConnection::_loadEntitiesUserConnection(
    std::size_t &buttonSendId, std::size_t &buttonPseudoId, std::size_t &buttonPasswordId)
{
    ecs::Entity &inputsEntity = _world->addEntity()
                                    .addComponent<MouseInputComponent>()
                                    .addComponent<KeyboardInputComponent>()
                                    .addComponent<ControllerButtonInputComponent>()
                                    .addComponent<ControllerJoystickInputComponent>()
                                    .addComponent<ActionQueueComponent>()
                                    .addComponent<AllowMouseAndKeyboardComponent>()
                                    .addComponent<AllowControllerComponent>();

    _setInputUserConnection(inputsEntity);
    sf::RenderWindow &window = _world->getResource<RenderWindowResource>().window;
    buttonPseudoId = createNewWritable(
        *(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 - 25, 200, 50, MenuStates::MAIN_MENU);
    buttonPasswordId = createNewWritable(
        *(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 * 2 - 25, 200, 50, MenuStates::MAIN_MENU);
    createNewText(*(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 - 65, 16, LayerLvL::TEXT,
        MenuStates::MAIN_MENU, "Enter your pseudo :");
    createNewText(*(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 * 2 - 65, 16, LayerLvL::TEXT,
        MenuStates::MAIN_MENU, "Enter your password :");
    buttonSendId = createNewButton(*(_world.get()), window.getSize().x / 2 - 100, window.getSize().y / 5 * 4 - 25, 200,
        50, ButtonActionMap::WRITABLE, LayerLvL::BUTTON, MenuStates::MAIN_MENU, "Connect to the game !");
    _world->addEntity()
        .addComponent<GraphicsRectangleComponent>(0, 0, 1920, 1080)
        .addComponent<Position>(0, 0)
        .addComponent<LayerLvL>(LayerLvL::layer_e::DECORATION)
        .addComponent<TextureName>(GraphicsTextureResource::BACKGROUND_LAYER)
        .getId();
}

void UserConnection::_runSystemsUserConnection(std::size_t buttonSendId)
{
    ecs::Entity &buttonSend = _world->getEntity(buttonSendId);

    while (_world->containsResource<RenderWindowResource>()
        && _world->getResource<RenderWindowResource>().window.isOpen()) {
        _world->runSystems();
        if (buttonSend.getComponent<Button>().IsClicked) {
            buttonSend.getComponent<Button>().IsClicked = false;
            break;
        }
    }
}

void UserConnection::userConnection()
{
    std::size_t buttonSendId = 0;
    std::size_t buttonPseudoId = 0;
    std::size_t buttonPasswordId = 0;
    bool validUserInformation = false;

    _loadResourcesUserConnection();
    _loadSystemsUserConnection();
    _loadEntitiesUserConnection(buttonSendId, buttonPseudoId, buttonPasswordId);
    while (!validUserInformation && _world->containsResource<RenderWindowResource>()
        && _world->getResource<RenderWindowResource>().window.isOpen()) {
        _runSystemsUserConnection(buttonSendId);
        _pseudo = _world->getEntity(buttonPseudoId).getComponent<WritableContent>().content;
        _password = _world->getEntity(buttonPasswordId).getComponent<WritableContent>().content;
        if (_pseudo.size() < 4 || _pseudo.size() > 10 || _password.size() < 4 || _password.size() > 10) {
            _pseudo = "";
            _password = "";
            throw error_lib::RTypeError("User connection invalid size");
        } else {
            validUserInformation = true;
        }
    }
}

const std::string &UserConnection::getPseudo() const { return _pseudo; }

const std::string &UserConnection::getPassword() const { return _password; }
