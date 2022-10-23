/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SendNewlyCreatedToServer
*/

#include "Transisthor/ECSLogic/Client/Systems/SendNewlyCreatedToServer.hpp"
#include "Transisthor/ECSLogic/Both/Components/Networkable.hpp"
#include "Transisthor/ECSLogic/Client/Components/NetworkServer.hpp"
#include "R-TypeLogic/Global/Components/AlliedProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageComponent.hpp"
#include "R-TypeLogic/Global/Components/DamageRadiusComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/Components/EnemyProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/LifeComponent.hpp"
#include "R-TypeLogic/Global/Components/NewlyCreated.hpp"
#include "R-TypeLogic/Global/Components/ObstacleComponent.hpp"
#include "R-TypeLogic/Global/Components/PlayerComponent.hpp"
#include "R-TypeLogic/Global/Components/PositionComponent.hpp"
#include "R-TypeLogic/Global/Components/ProjectileComponent.hpp"
#include "R-TypeLogic/Global/Components/SizeComponent.hpp"
#include "R-TypeLogic/Global/Components/VelocityComponent.hpp"
#include "R-TypeLogic/Global/Components/WeightComponent.hpp"

using namespace transisthor::ecslogic;
using namespace rtypelogic::global;
using namespace ecs;

void SendNewlyCreatedToServer::runSystem(World &world)
{
    std::vector<std::shared_ptr<Entity>> servers = world.joinEntities<NetworkServer>();
    std::vector<std::shared_ptr<Entity>> joinedNewlyCreated = world.joinEntities<NewlyCreated>();
    std::vector<unsigned short> serverIdList;

    auto addToClientList = [&serverIdList](std::shared_ptr<Entity> entityPtr) {
        serverIdList.emplace_back(entityPtr.get()->getComponent<NetworkServer>().id);
    };

    auto update = [this, &world, &serverIdList](std::shared_ptr<Entity> entityPtr) {
        NewlyCreated &newlyCreated = entityPtr->getComponent<NewlyCreated>();

        if (!newlyCreated.isClientInstance)
            return;
        if (newlyCreated.uuid == "") {
            entityPtr->removeComponent<NewlyCreated>();
            return;
        }
        if (entityPtr->contains<AlliedProjectile>() && newlyCreated.sended == false) {
            std::cerr << newlyCreated.uuid << std::endl;
            world.getTransisthorBridge()->transitEcsDataToNetworkDataEntityAlliedProjectile(
                entityPtr->getComponent<Networkable>().id, entityPtr->getComponent<AlliedProjectile>().parentNetworkId,
                newlyCreated.uuid, serverIdList);
            newlyCreated.sended = true;
        }
        return;
    };

    std::for_each(servers.begin(), servers.end(), addToClientList);
    if (!serverIdList.empty())
        std::for_each(joinedNewlyCreated.begin(), joinedNewlyCreated.end(), update);
}
