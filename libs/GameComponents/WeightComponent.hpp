/*
** EPITECH PROJECT, 2022
** Project
** File description:
** WeightComponent
*/

#ifndef WEIGHTCOMPONENT_HPP_
#define WEIGHTCOMPONENT_HPP_

#include "Component.hpp"

namespace ecs
{
    /// @brief The Weight class, almost used for everything, used in gravity system
    class Weight : public Component{
      public:
        /// @brief weight of the entity
        short weight;

        /// @brief Constructor of the Weight Component
        /// @param newWeight the weight
        Weight(short newWeight) : weight(newWeight) {};
        /// @brief Copy Constructor of the Weight Component
        /// @param old the copy of the Weight component
        Weight(const Weight &old) : weight(old.weight) {};
        /// @brief Default Destructor
        ~Weight() = default;
    };
} // namespace ecs

#endif /* !WEIGHTCOMPONENT_HPP_ */
