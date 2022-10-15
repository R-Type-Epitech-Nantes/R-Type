/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** KeyboardInputComponent
*/

#ifndef KEYBOARDINPUTCOMPONENT_HPP_
#define KEYBOARDINPUTCOMPONENT_HPP_

#include "Component/Component.hpp"
#include "World/World.hpp"
#include "ActionQueueComponent.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

namespace ecs
{
    /// @brief This component class stores an unsorted map of action/value pair.
    /// This class is created in order to find an action depending on a key pressed or released.
    /// It inherits from Component.
    class KeyboardInputComponent : public Component {
        public:
            /// @brief This unordered_map links SFML key input to an action/value pair enum.
            std::unordered_map<sf::Keyboard::Key, std::pair<ActionQueueComponent::inputAction_e, float>> keyboardMapActions;
            // std::unordered_map<sf::Keyboard::Key, std::_Bind<void (ecs::InputManagement::*(ecs::KeyboardInputComponent, std::shared_ptr<ecs::World>, float))(ecs::World &world, float move)>> keyboardMapActions;

        /// @brief Constructor of the class.
        KeyboardInputComponent() = default;

        /// @brief Default destructor of the class.
        ~KeyboardInputComponent() = default;
    };
} // namespace ecs

#endif /* !KEYBOARDINPUTCOMPONENT_HPP_ */
