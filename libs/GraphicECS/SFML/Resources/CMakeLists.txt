set(GRAPHIC_SRC_RESOURCE_ROOT ${PROJECT_SOURCE_DIR}/libs/GraphicECS/SFML/Resources)

set(SRC_GRAPHIC_RESOURCE
    ${GRAPHIC_SRC_RESOURCE_ROOT}/RenderWindowResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/GraphicsFontResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/GraphicsTextureResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/GraphicsTextureResource.cpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/SoundResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/SoundResource.cpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/MusicResource.hpp
    ${GRAPHIC_SRC_RESOURCE_ROOT}/MusicResource.cpp
    PARENT_SCOPE
)
