set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/EntityManipulation/ButtonManipulation)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs/R-TypeLogic/EntityManipulation/ButtonManipulation)

set(SRC
    ${SRC_ROOT}/SharedResources/ButtonActionMap.cpp
    ${INC_ROOT}/SharedResources/ButtonActionMap.hpp
    ${INC_ROOT}/SharedResources/MenuStates.hpp
    ${INC_ROOT}/SharedResources/GameStates.hpp
    ${INC_ROOT}/Components/DisplayState.hpp
    ${INC_ROOT}/Components/ActionName.hpp
)

set(TARGET ${PROJECT_NAME}_RTypeLogicButtonManipulation)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)

install(TARGETS ${TARGET} DESTINATION bin)