/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Sender
*/

/// @file libs/Communicator/Sender.hpp

#ifndef SENDER_HPP_
#define SENDER_HPP_

#include <vector>
#include "Client.hpp"

namespace communicator_lib
{
    /// @brief Sending data module
    class Sender {
      public:
        /// @brief The sender object constructor
        Sender();

        /// @brief The sender object constructor
        /// @param receiverPort The receiver port value
        Sender(unsigned short receiverPort);

        /// @brief Destroy the Sender object
        ~Sender() = default;

        /// @brief Send data to a given client
        /// @param client The client informations
        /// @param data The given data to transfer
        /// @param size Size of the data to transfer (sizeof(data) * quantity)
        /// @param type Data type (Refer to RFC)
        void sendDataToAClient(Client &client, void *data, size_t size, unsigned short type);

        /// @brief Send data to a given vector of clients
        /// @param clients The clients informations vector
        /// @param data The given data to transfer
        /// @param size Size of the data to transfer (sizeof(data) * quantity)
        /// @param type Data type (Refer to RFC)
        void sendDataToMultipleClients(std::vector<Client> clients, void *data, size_t size, unsigned short type);

      private:
        /// @brief Create a communication header which contain Receiver Port | Communication Type
        /// @param communicationType The communication type
        /// @return Created communication header
        void *generateDataHeader(unsigned short communicationType);

        /// @brief Port of the associated receiver module
        unsigned short _receiverPort;
    };
} // namespace communicator_lib

#endif /* !SENDER_HPP_ */
