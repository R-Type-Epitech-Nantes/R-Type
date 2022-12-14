/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextureName
*/

#ifndef TEXTURENAME_HPP_
#define TEXTURENAME_HPP_

#include "Component/Component.hpp"
#include "GraphicECS/SFML/Resources/GraphicsTextureResource.hpp"

using namespace graphicECS::SFML::Resources;

namespace graphicECS::SFML::Components
{
    /// @brief TextureName store the key as enum to the corresponding texture stores in shared resource.
    class TextureName : public ecs::Component {
      public:
        /// @brief The texture name stores to find the corresponding textureName.
        GraphicsTextureResource::textureName_e textureName;

        /// @brief Constructor of the TextureName component
        /// @param newTextureName The value to set in the textureName, corresponding
        /// on the sf::Texture load in shared resource GraphicsTexture.
        TextureName(GraphicsTextureResource::textureName_e newTextureName = GraphicsTextureResource::UNDEFINED)
            : textureName(newTextureName){};

        /// @brief Default destructor of TextureName component.
        ~TextureName() = default;
    };
} // namespace graphicECS::SFML::Components

#endif /* !TEXTURENAME_HPP_ */
