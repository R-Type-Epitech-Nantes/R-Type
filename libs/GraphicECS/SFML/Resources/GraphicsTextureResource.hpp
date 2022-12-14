/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsTextureResource
*/

#ifndef GRAPHICSTEXTURERESOURCE_HPP_
#define GRAPHICSTEXTURERESOURCE_HPP_

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "Resource/Resource.hpp"
#include <unordered_map>

namespace graphicECS::SFML::Resources
{

    /// @brief This resource class stores a map of Graphical SFML textures to be set on Shapes.
    class GraphicsTextureResource : public ecs::Resource {
      public:
        /// @brief Enumeration of all available Textures
        enum textureName_e {
            UNDEFINED,
            BLUE_PLAYER_STATIC_1,
            BLUE_PLAYER_STATIC_2,
            BLUE_PLAYER_STATIC_3,
            BLUE_PLAYER_STATIC_4,
            BLUE_PLAYER_STATIC_5,
            PINK_PLAYER_STATIC_1,
            PINK_PLAYER_STATIC_2,
            PINK_PLAYER_STATIC_3,
            PINK_PLAYER_STATIC_4,
            PINK_PLAYER_STATIC_5,
            GREEN_PLAYER_STATIC_1,
            GREEN_PLAYER_STATIC_2,
            GREEN_PLAYER_STATIC_3,
            GREEN_PLAYER_STATIC_4,
            GREEN_PLAYER_STATIC_5,
            YELLOW_PLAYER_STATIC_1,
            YELLOW_PLAYER_STATIC_2,
            YELLOW_PLAYER_STATIC_3,
            YELLOW_PLAYER_STATIC_4,
            YELLOW_PLAYER_STATIC_5,
            PLAYER_UP,
            PLAYER_DOWN,
            BASIC_ENEMY,
            FIRE_ENEMY,
            ELECTRIC_ENEMY,
            ICE_ENEMY,
            BOSS,
            ENEMY_UP,
            ENEMY_DOWN,
            BACKGROUND_LAYER,
            BACKGROUND_LAYER_1,
            BACKGROUND_LAYER_2,
            BACKGROUND_LAYER_3,
            OBSTACLE_1,
            OBSTACLE_2,
            OBSTACLE_3,
            PROJECTILE_ALLY,
            PROJECTILE_ENEMY_BASIC,
            PROJECTILE_ENEMY_FIRE,
            PROJECTILE_ENEMY_ELECTRIC,
            PROJECTILE_ENEMY_ICE,
            BUTTON,
            WRITABLE,
            WRITABLE_SELECTED,
            WRITABLE_BUTTON,
            NATURAL_PROJECTILE
        };

        /// @brief Name of map which contains Textures.
        using TexturesList = std::unordered_map<textureName_e, std::shared_ptr<sf::Texture>>;

        /// @brief Default Constructor of GraphicTextureResource.
        GraphicsTextureResource() = default;

        /// @brief Add a Texture from it's Texture Path passed as parameter
        /// @param texture_e Enum of the Texture
        /// @param texturePath The texture path to be used.
        /// @param position The position of the image to start getting the texture
        /// @param size The size on an image to get to create a texture
        inline GraphicsTextureResource(const textureName_e texture_e, const std::filesystem::path &texturePath,
            const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Vector2f &size = sf::Vector2f(0, 0))
        {
            addTexture(texture_e, texturePath, position, size);
        }

        /// @brief Add a texture to the TexturesList
        /// @param texture_e Enum which give the name of the Texture
        /// @param texturePath Path of the Texture
        void addTexture(const textureName_e texture_e, const std::filesystem::path &texturePath,
            const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Vector2f &size = sf::Vector2f(0, 0));

        /// @brief Remove a texture to the textureList
        /// @param texture Enum which give the name of Texture
        inline void removeTexture(const textureName_e texture) { _texturesList.erase(texture); };

        /// @brief Default destructor of the class.
        ~GraphicsTextureResource() = default;

        TexturesList _texturesList;
    };
} // namespace graphicECS::SFML::Resources

#endif /* !GRAPHICSTEXTURERESOURCE_HPP_ */
