
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Room)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/Room)

set(TARGET_ROOM r-type_room)

set(SRC_ROOM
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/Room.cpp
    ${INC_ROOT}/Room.hpp
)

add_executable(${TARGET_ROOM} ${SRC_ROOM})

set_property(TARGET ${TARGET_ROOM} PROPERTY MSVC_RUNTIME_LIBRARY "")

set_target_properties(${TARGET_ROOM}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${TARGET_ROOM}
    ${PROJECT_NAME}_transisthor
    ${PROJECT_NAME}_RTypeLogicRoom
    ${PROJECT_NAME}_argumentHandler
    ${PROJECT_NAME}_database
)

install(TARGETS ${TARGET_ROOM} DESTINATION bin)