set(SRC_RTYPE_LOGIC_SYSTEMS_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/Server/Systems)

set(SRC_RTYPE_LOGIC_SERVER_SYSTEMS
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/DeathLifeSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/LifeTimeDeathSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/DecreaseLifeTimeSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/CollidableSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/CollidableSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/EnemiesPatterns.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/EnemiesPatterns.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/EnemyShootSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/EnemyShootSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/DisconnectableSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/DisconnectableSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/RemoveAfkSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/RemoveAfkSystem.hpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/MobGenerationSystem.cpp
    ${SRC_RTYPE_LOGIC_SYSTEMS_ROOT}/MobGenerationSystem.hpp
    PARENT_SCOPE
)
