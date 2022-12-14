/*
** EPITECH PROJECT, 2022
** R-Type [WSL : Ubuntu]
** File description:
** AnimationFrequencyComponent
*/

#ifndef ANIMATIONFREQUENCYCOMPONENT_HPP_
#define ANIMATIONFREQUENCYCOMPONENT_HPP_

#include <chrono>
#include "Component/Component.hpp"

namespace graphicECS::SFML::Components
{
    /// @brief This component allows to know the frequency between each frame of an animation.
    class AnimationFrequencyComponent : public ecs::Component {
      public:
        /// @brief The frequency between each frame of an animation as seconds.
        std::chrono::duration<double> frequency;

        /// @brief The default frequency of the animation as seconds.
        const std::chrono::duration<double> baseFrequency;

        /// @brief Construct the class to set default values.
        /// @param d Frequency to set the baseFrequency of the animation. Default value is 0.5 seconds.
        AnimationFrequencyComponent(const double &d = 0.5)
            : frequency(std::chrono::duration<double>(d)), baseFrequency(std::chrono::duration<double>(d)){};

        /// @brief Default destructor.
        ~AnimationFrequencyComponent() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !ANIMATIONFREQUENCYCOMPONENT_HPP_ */
