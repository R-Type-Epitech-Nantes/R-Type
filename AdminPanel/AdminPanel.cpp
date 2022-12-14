/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** AdminPanel
*/

#include "AdminPanel.hpp"
#include "Error/Error.hpp"

using namespace error_lib;
using namespace communicator_lib;
using namespace admin_panel;

std::vector<AdminPanel::PanelCommand> commandList = {{"updatePassword", "", {}}, {"updateName", "", {}},
    {"ban", "", {}}, {"mute", "", {}}, {"unban", "", {}}, {"unmute", "", {}}, {"delete", "", {}}, {"promote", "", {}},
    {"unpromote", "", {}}, {"get", "", {}}, {"scoreboard", "", {}}};

AdminPanel::AdminPanel(std::string address, unsigned short port, std::string serverAddress, unsigned short serverPort)
{
    _networkInformations = Client(address, port);
    _communicatorInstance = std::make_shared<Communicator>(_networkInformations);
    _serverEndpoint = Client(serverAddress, serverPort);
    _waitingForAnswer = 0;
    _isAuth = false;
    _pseudo = "";
    _state = true;
    _requestAction["updatePassword"] = std::bind(&AdminPanel::_updatePasswordAction, this, std::placeholders::_1);
    _requestAction["updateName"] = std::bind(&AdminPanel::_updateNameAction, this, std::placeholders::_1);
    _requestAction["ban"] = std::bind(&AdminPanel::_banAction, this, std::placeholders::_1);
    _requestAction["unban"] = std::bind(&AdminPanel::_unbanAction, this, std::placeholders::_1);
    _requestAction["mute"] = std::bind(&AdminPanel::_muteAction, this, std::placeholders::_1);
    _requestAction["unmute"] = std::bind(&AdminPanel::_unmuteAction, this, std::placeholders::_1);
    _requestAction["promote"] = std::bind(&AdminPanel::_promoteAction, this, std::placeholders::_1);
    _requestAction["unpromote"] = std::bind(&AdminPanel::_unpromoteAction, this, std::placeholders::_1);
    _requestAction["get"] = std::bind(&AdminPanel::_getStatsAction, this, std::placeholders::_1);
    _requestAction["scoreboard"] = std::bind(&AdminPanel::_scoreboardAction, this, std::placeholders::_1);
}

void AdminPanel::startLoop()
{
    _communicatorInstance->startReceiverListening();
    while (_state) {
        try {
            auto databaseAnswer = _communicatorInstance.get()->getLastMessage();
            if (databaseAnswer.message.type == 11) {
                std::cout << "Invalid login, please retry." << std::endl;
                return;
            }
            if (databaseAnswer.message.type == 15) {
                _communicatorInstance->utilitaryAskForADatabaseValue(_pseudo, "Moderator", {0});
            }
            if (databaseAnswer.message.type == 41)
                _handleAReceivedData(databaseAnswer);
            if (databaseAnswer.message.type == 45)
                _handleAReceivedScoreboard(databaseAnswer);
            if (databaseAnswer.message.type == 43) {
                std::cout << "Wanted client doesn't exist inside the database." << std::endl;
                _waitingForAnswer -= 1;
            }
        } catch (NetworkError &error) {
        }
        if (!_waitingForAnswer) {
            if (!_isAuth) {
                _authentificationProcess();
            } else {
                _getARequest();
            }
        }
    }
}

void AdminPanel::_authentificationProcess()
{
    std::string pseudo;
    std::string password;

    std::cout << "Welcome to the Admin panel !" << std::endl;
    std::cout << "Please refer your name : ";
    std::cin >> pseudo;
    std::cout << "Welcome : " << pseudo << " ! Now, your password : ";
    std::cin >> password;
    unsigned short pseudoSize = pseudo.size();
    unsigned short passwordSize = password.size();
    unsigned short offset = 0;
    void *networkData = std::malloc(sizeof(char) * (pseudoSize + passwordSize) + sizeof(unsigned short) * 2);

    if (networkData == nullptr)
        throw MallocError("Malloc failed.");
    std::memcpy(networkData, &pseudoSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), pseudo.c_str(), sizeof(char) * pseudoSize);
    offset += sizeof(char) * pseudoSize;
    std::memcpy((void *)((char *)networkData + offset), &passwordSize, sizeof(unsigned short));
    offset += sizeof(unsigned short);
    std::memcpy((void *)((char *)networkData + offset), password.c_str(), sizeof(char) * passwordSize);
    offset += sizeof(char) * passwordSize;
    _communicatorInstance.get()->sendDataToAClient(_serverEndpoint, networkData, offset, 14);
    std::free(networkData);
    _pseudo = pseudo;
    _waitingForAnswer = 1;
    std::cout << "Request send to the server, please wait." << std::endl;
}

void AdminPanel::_handleAReceivedData(CommunicatorMessage databaseAnswer)
{
    std::string value = _communicatorInstance->utilitaryReceiveDatabaseValue(databaseAnswer);

    _waitingForAnswer -= 1;
    if (!_isAuth) {
        if (value != "1") {
            std::cout << "Your note an admin user ;)" << std::endl;
        } else {
            std::cout << "Authentification succeed." << std::endl;
            _isAuth = true;
        }
        return;
    }
    std::cout << value << std::endl;
}

void AdminPanel::_handleAReceivedScoreboard(CommunicatorMessage databaseAnswer)
{
    std::map<std::string, int> scoreboard = _communicatorInstance->utilitaryReceiveScoreboard(databaseAnswer);
    std::map<int, std::string> sortedScoreboard;

    for (auto &it : scoreboard)
        sortedScoreboard.insert({it.second, it.first});
    for (auto it = sortedScoreboard.rbegin(); it != sortedScoreboard.rend(); ++it) {
        std::cerr << it->second << " -> " << it->first << std::endl;
    }
    _waitingForAnswer -= 1;
}

AdminPanel::PanelCommand AdminPanel::_parseAClientRequest(std::string clientRequest)
{
    AdminPanel::PanelCommand panelCommand;
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    std::size_t counter = 0;

    while ((pos = clientRequest.find(delimiter)) != std::string::npos) {
        token = clientRequest.substr(0, pos);
        if (counter == 0)
            panelCommand.keyWord = std::string(token);
        if (counter == 1)
            panelCommand.userName = std::string(token);
        if (counter >= 2)
            panelCommand.options.push_back(std::string(token));
        clientRequest.erase(0, pos + delimiter.length());
        counter++;
    }
    if (counter == 0)
        panelCommand.keyWord = std::string(clientRequest);
    if (counter == 1)
        panelCommand.userName = std::string(clientRequest);
    if (counter >= 2)
        panelCommand.options.push_back(std::string(clientRequest));
    return panelCommand;
}

void AdminPanel::_getARequest()
{
    std::string clientRequest;

    std::cout << "Enter your request : ";
    std::getline(std::cin, clientRequest);
    AdminPanel::PanelCommand parsedRequest = _parseAClientRequest(clientRequest);
    if (_requestAction.find(parsedRequest.keyWord) == _requestAction.end()) {
        std::cout << "This is not a valid command. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _requestAction[parsedRequest.keyWord](parsedRequest);
}

void AdminPanel::_updatePasswordAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.options.size() != 1) {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 5, parsedRequest.options.at(0), {0});
}

void AdminPanel::_updateNameAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.options.size() != 1) {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 4, parsedRequest.options.at(0), {0});
}

void AdminPanel::_banAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 1, "1", {0});
}

void AdminPanel::_unbanAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 1, "0", {0});
}

void AdminPanel::_muteAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 2, "1", {0});
}

void AdminPanel::_unmuteAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 2, "0", {0});
}

void AdminPanel::_promoteAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 3, "1", {0});
}

void AdminPanel::_unpromoteAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _communicatorInstance->utilitarySetADatabaseValue(parsedRequest.userName, 3, "0", {0});
}

void AdminPanel::_getStatsAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    for (auto it : parsedRequest.options) {
        _waitingForAnswer += 1;
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, it, {0});
    }
    if (parsedRequest.options.empty()) {
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "UserID", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "UserName", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "CreationDate", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "Password", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "Moderator", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "Banned", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "Muted", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "HighestScore", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "Deaths", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "KilledEnemies", {0});
        _communicatorInstance->utilitaryAskForADatabaseValue(parsedRequest.userName, "GamesPlayed", {0});
        _waitingForAnswer += 11;
    }
}

void AdminPanel::_scoreboardAction(AdminPanel::PanelCommand parsedRequest)
{
    if (parsedRequest.userName == "") {
        std::cout << "Invalid command parameters. Please refer to the Notion protocol." << std::endl;
        return;
    }
    _waitingForAnswer += 1;
    _communicatorInstance->utilitaryAskForALeaderboard(parsedRequest.userName, {0});
}
