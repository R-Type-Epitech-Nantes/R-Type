/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** CreateWritableButton
*/

#include "CreateWritableButton.hpp"
#include <mutex>
#include "R-TypeLogic/Global/Components/ButtonComponent.hpp"
#include "R-TypeLogic/Global/Components/LayerLvL.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "GraphicECS/SFML/Components/AssociatedIdComponent.hpp"
#include "GraphicECS/SFML/Components/WritableButtonActionComponent.hpp"

namespace ecs
{
    std::size_t createNewWritableButton(World &world, const int posX, const int posY, const int sizeX, const int sizeY,
        std::function<void(World &, Entity &, std::string &)> actionFunction, MenuStates::menuState_e state, std::size_t associatedWritableId)
    {
        Entity &entity = world.addEntity();
        auto guard = std::lock_guard(entity);
        entity.addComponent<Button>()
            .addComponent<Size>(sizeX, sizeY)
            .addComponent<Position>(posX, posY)
            .addComponent<LayerLvL>(LayerLvL::WRITABLE_BUTTON)
            .addComponent<ActionName>(ButtonActionMap::WRITABLE_BUTTON)
            .addComponent<DisplayState>(state)
            .addComponent<graphicECS::SFML::Components::AssociatedId>(std::vector<std::size_t>{associatedWritableId})
            .addComponent<graphicECS::SFML::Components::WritableButtonAction>(actionFunction);
        return entity.getId();
    }
} // namespace ecs
