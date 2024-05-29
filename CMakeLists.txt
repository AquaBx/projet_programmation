cmake_minimum_required(VERSION 3.27)
project(projet_programmation)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-c -Wall -ggdb)

include_directories(${PROJECT_SOURCE_DIR}/libs/SDL2/include/)
include_directories(${PROJECT_SOURCE_DIR}/libs/SDL2/include/SDL2/)
include_directories(${PROJECT_SOURCE_DIR}/src/)

set(flags
)

set(exec
        src/main.cpp

        src/game/game.h
        src/game/game.cpp

        src/game/context.h
        src/game/context.cpp

        src/event.h
        src/event.cpp

        src/physics/physics.h
        src/physics/physics.cpp

        src/physics/aabb.h

        src/entity/entity.h
        src/entity/entity.cpp

        src/entity/interactible.h
        src/entity/interactible.cpp

        src/entity/player.h
        src/entity/player.cpp

        src/camera.h
        src/camera.cpp

        src/utils/vec2.h
        src/utils/vec4.h

        src/color.h
        src/renderer.h
        src/renderer.cpp
        
        src/cluster.h
        src/cluster.cpp

        src/GUI/health_bar.h
        src/GUI/health_bar.cpp

        src/map/map.h
        src/map/map.cpp

        src/entity/sprite.h
        src/entity/sprite.cpp

        src/entity/animated_sprite.h
        src/entity/animated_sprite.cpp

        src/entity/collidable_entity.h
        src/entity/collidable_entity.cpp

        src/GUI/gui_component.h
        src/GUI/gui_component.cpp

        src/physics/collidable.h

        src/input.h
        src/input.cpp

        src/entity/cow.h
        src/entity/cow.cpp
        src/entity/tomato_crop.h
        src/entity/crop.cpp
        src/entity/crop.h
        src/entity/wheat_crop.h
        src/GUI/food_bar.cpp
        src/GUI/food_bar.h
        src/entity/fusee.cpp
        src/entity/fusee.h


        src/map/serializer.h
        src/map/serializer.cpp
        
        src/texture_manager.h
        src/texture_manager.cpp
        src/entity/pnj.cpp
        src/entity/pnj.h
        src/entity/chicken.cpp
        src/entity/chicken.h
)

# SDL2_image sources
FILE(GLOB SDL2_image_src CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/libs/SDL2_image/src/*.c)
list(APPEND exec ${SDL2_image_src})

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    list(APPEND flags WIN32)

    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "ARM64")
        set(libs ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/msvc_arm64/SDL2.lib)
    ELSE()
        set(libs ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/msvc_x64/SDL2.lib)
    ENDIF()
ELSE()
    set(libs ${PROJECT_SOURCE_DIR}/libs/SDL2/bin/mingw_x64/SDL2.dll)
ENDIF()

add_executable(projet_programmation ${flags} ${exec})

target_link_libraries(${PROJECT_NAME} ${libs})