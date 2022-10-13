/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

/// @file Server/Room.cpp

#include "Room.hpp"
#include "Error/Error.hpp"
#include "GameComponents/PositionComponent.hpp"
#include "GameEntityManipulation/CreateEntitiesFunctions/CreateObstacle.hpp"
#include "Transisthor/TransisthorECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Components/NetworkClient.hpp"
#include "Transisthor/TransisthorECSLogic/Server/Systems/SendToClient.hpp"

using namespace server_data;
using namespace error_lib;
using namespace communicator_lib;
using namespace ecs;

Room::Room()
{
    _id = 0;
    _networkInformations = Client();
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = RoomState::UNDEFINED;
    _remainingPlaces = 4;
}

Room::Room(unsigned short id, Client networkInformations)
{
    _id = id;
    _networkInformations = networkInformations;
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _worldInstance = std::make_shared<World>(1);
    _transisthorInstance = std::make_shared<Transisthor>(*(_communicatorInstance.get()), *(_worldInstance.get()));
    _communicatorInstance.get()->setTransisthorBridge(_transisthorInstance);
    _worldInstance.get()->setTransisthorBridge(_communicatorInstance.get()->getTransisthorBridge());
    _state = RoomState::UNDEFINED;
    _remainingPlaces = 4;
}

struct Temp : public System {
    void run(World &world)
    {
        std::vector<std::shared_ptr<Entity>> joined = world.joinEntities<Position>();

        for (std::shared_ptr<Entity> entityPtr : joined) {
            Position &pos = entityPtr->getComponent<Position>();

            pos.x = 60;
            pos.y = 120;
        }
    }
};

void Room::startLobbyLoop(void)
{
    CommunicatorMessage connexionDemand;

    _communicatorInstance.get()->startReceiverListening();
    _worldInstance->addSystem<Temp>();
    _worldInstance->addSystem<SendToClient>();
    _state = RoomState::LOBBY;
    while (_state != RoomState::ENDED && _state != RoomState::UNDEFINED) {
        try {
            connexionDemand = _communicatorInstance.get()->getLastMessage();
            if (connexionDemand.message.type == 10)
                holdANewConnexionRequest(connexionDemand);
        } catch (NetworkError &error) {
        }
        _worldInstance.get()->runSystems(); /// WILL BE IMPROVED IN PART TWO (THREAD + CLOCK)
    }
}

void Room::holdANewConnexionRequest(CommunicatorMessage connexionDemand)
{
    if (_remainingPlaces == 0) {
        /// SEND A PROTOCOL 21
        return;
    }
    std::cerr << "Room " << _id << " received a connexion protocol." << std::endl;
    _worldInstance->addEntity().addComponent<NetworkClient>(connexionDemand.message.clientInfo.getId());
    /// SEND A PROTOCOL 22
    _remainingPlaces -= 1;
}
