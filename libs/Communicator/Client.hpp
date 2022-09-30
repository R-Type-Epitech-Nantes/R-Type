/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** client
*/

/// @file libs/Communicator/Client.hpp

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>

namespace communicator_lib
{
    /// @brief A representation of a client (Address + Port)
    class Client {
      public:
        /// @brief Construct a new Client object
        /// @param address The address of the client
        /// @param port The port of the client
        Client(std::string address = "127.0.0.1", long port = 0);

        /// @brief Destroy the Client object
        ~Client();

        /// @brief Get the Address value
        /// @return std::string A copy of the address value
        inline std::string getAddress(void) const { return _address; };

        /// @brief Get the Port value
        /// @return long The value of the port
        inline long getPort(void) const { return _port; };

        /// @brief Set the Address value
        /// @param address The newly address
        inline void setAddress(std::string address) { _address = address; };

        /// @brief Set the Port value
        /// @param port The new port number
        inline void setPort(long port) { _port = port; };

      private:
        /// @brief The ip address of the client (127.0.0.1 by default)
        std::string _address;
        /// @brief The port of the client (0 by default)
        unsigned short _port;
    };

    /// @brief Overload of the == operator to compare two clients
    /// @param left The left param of the comparison
    /// @param right The right param of the comparison
    /// @return true If the two clients are the same
    /// @return false If the two clients are different
    inline bool operator==(const Client &left, const Client &right)
    {
        return ((left.getPort() == right.getPort()) && (left.getAddress() == right.getAddress()));
    }
} // namespace communicator_lib

#endif /* !CLIENT_HPP_ */
