cmake_minimum_required(VERSION 3.26)
project(game_engine_tobe)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
#add_executable(my_game ${MY_SOURCES})
add_executable(game_engine_tobe
        src/main.cpp src/world/world_generator.cpp
        src/world/Tile.cpp
        src/entities/Entity.cpp
        src/entities/Player.cpp
        src/utilities/Camera.cpp
        src/world/World_Handler.cpp)
target_link_libraries(game_engine_tobe PRIVATE SDL2::SDL2)


