cmake_minimum_required(VERSION 3.27)
project(project_game2d)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(project_game2d main.cpp
        Player.cpp
        Player.h
        vmath.cpp
        vmath.h
        maps/Map.cpp
        maps/Map.h
        Enemy.cpp
        Enemy.h)
target_link_libraries(project_game2d sfml-graphics)