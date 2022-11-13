/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** main for the client
*/

#include "ArgumentHandler/ArgumentHandler.hpp"
#include "ClientRoom.hpp"
#include "Error/Error.hpp"
#include "UserConnection.hpp"

using namespace client_data;
using namespace argument_handler;

int main(int ac, char **av)
{
    ArgumentHandler argumentHandler = ArgumentHandler(ac, av);
    ArgumentHandler::ClientInformation clientInformation;

    try {
        clientInformation = argumentHandler.extractClientInformation();
    } catch (std::exception &exc) {
        std::cerr << exc.what() <<std::endl;
        return 84;
    }
    ClientRoom client = ClientRoom(clientInformation.clientAddress, clientInformation.clientPort,
        clientInformation.serverAddress, clientInformation.serverPort);

    if (client.startGame() == 84)
        return 84;
    return (0);
}
