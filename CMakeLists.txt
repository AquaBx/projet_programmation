cmake_minimum_required(VERSION 3.27)
project(projet_programmation)

set(CMAKE_CXX_STANDARD 11)



add_compile_options(-c -Wall -ggdb)

include_directories(${PROJECT_SOURCE_DIR}/libs/SDL2/include/)

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_executable(projet_programmation WIN32 src/main.cpp)

    IF("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "ARM64")
        target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/msvc_arm64/SDL2.lib)
    ELSE()
        target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/msvc_x64/SDL2.lib)
    ENDIF()

ELSE()
    add_executable(projet_programmation src/main.cpp)

    target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/SDL2/bin/mingw_x64/SDL2.dll)
ENDIF()