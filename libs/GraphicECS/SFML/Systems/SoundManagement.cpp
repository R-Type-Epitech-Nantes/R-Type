/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundManagement
*/

#include "SoundManagement.hpp"

using namespace graphicECS::SFML::Components;
using namespace graphicECS::SFML::Resources;

namespace graphicECS::SFML::Systems
{
    void SoundManagement::run(World &world)
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<SoundComponent>();

        if (!world.containsResource<SoundResource>() || !world.getResource<SoundResource>().playSound)
            return;
        auto stopSound = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            SoundComponent soundComponent = entityPtr.get()->getComponent<SoundComponent>();
            if (!world.getResource<SoundResource>()._soundsList.contains(soundComponent.sound_e))
                return;
            sf::SoundBuffer new_buff(*world.getResource<SoundResource>()._soundsList.at(soundComponent.sound_e));
            sf::Sound sound;

            sound.setBuffer(new_buff);
            if (soundComponent._status == sf::SoundSource::Status::Stopped && sound.getStatus() != sf::Sound::Stopped) {
                sound.stop();
            }
            if (soundComponent._status == sf::SoundSource::Status::Paused && sound.getStatus() != sf::Sound::Paused) {

                sound.pause();
            }
            if (soundComponent._status == sf::SoundSource::Status::Playing && sound.getStatus() != sf::Sound::Playing) {

                 sound.play();
            }
        };
        std::for_each(joined.begin(), joined.end(), stopSound);
    }
} // namespace graphicECS::SFML::Systems
