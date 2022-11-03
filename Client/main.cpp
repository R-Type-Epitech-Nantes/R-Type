/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** main for the client
*/

#include "ArgumentHandler/ArgumentHandler.hpp"
#include "ClientRoom.hpp"

using namespace client_data;
using namespace argument_handler;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::ClientInformation clientInformation = argumentHandler.extractClientInformation();
    ClientRoom client = ClientRoom(clientInformation.clientAddress, clientInformation.clientPort,
        clientInformation.serverAddress, clientInformation.serverPort);

    client.startGame();
//    client.startLobbyLoop();
//    client.startSoloLoop();
    return (0);
}
