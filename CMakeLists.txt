cmake_minimum_required(VERSION 3.29)
project(realm-of-spells-desktop)

file(
        GLOB_RECURSE
        SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
