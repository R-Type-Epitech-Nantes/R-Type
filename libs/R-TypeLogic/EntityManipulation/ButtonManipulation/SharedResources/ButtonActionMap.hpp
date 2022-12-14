/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ButtonActionMap
*/

#ifndef BUTTONACTIONMAP_HPP_
#define BUTTONACTIONMAP_HPP_

#include <functional>
#include "Resource/Resource.hpp"
#include "World/World.hpp"
#include <unordered_map>

namespace ecs
{
    /// @brief This resource class stores a map of button action to be executed on click
    class ButtonActionMap : public Resource {
      public:
        /// @brief Enumeration of all the available actions
        enum buttonAction_e {
            UNDEFINED,
            GO_MAIN_MENU,
            GO_SOLO_GAME,
            GO_LOBBY,
            GO_MULTI_GAME,
            GO_OPTION,
            PAUSE,
            RESUME,
            QUIT,
            CONNECT_TO_ROOM,
            CREATE_A_ROOM,
            MATCHMAKED_ROOM,
            WRITABLE,
            WRITABLE_BUTTON,
            SWITCH_SOUND,
            SWITCH_MUSIC
        };

        /// @brief Map's name which contains the actions
        using ActionList = std::unordered_map<buttonAction_e, std::function<void(World &, Entity &)>>;

        /// @brief Constructor of the map, calling the addAction Method
        /// PLEASE DO NOT USE THE DEFAULT CONSTRUCTOR
        /// @param action Enum of the Action
        /// @param fctPtr The fonction to be executed
        ButtonActionMap(const buttonAction_e &action = ButtonActionMap::UNDEFINED,
            std::function<void(World &, Entity &)> fctPtr = std::function<void(World &, Entity &)>());

        /// @brief Add a action to the ActionList
        /// @param action Enum of the Action
        /// @param fctPtr The fonction to be executed
        void addAction(const buttonAction_e newAction, std::function<void(World &, Entity &)> fctPtr);

        /// @brief Default Constructor of the class
        ~ButtonActionMap() = default;

        /// @brief The map where the actions are stored
        ActionList actionList;
    };
} // namespace ecs

#endif /* !BUTTONACTIONMAP_HPP_ */
