cmake_minimum_required(VERSION 3.29)
project(realm-of-spells-desktop)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(raylib)

# list all sources
file(
        GLOB_RECURSE
        SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# adding all the source directories to include path
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)
