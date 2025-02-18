cmake_minimum_required(VERSION 3.29)
project(realm-of-spells-launcher)

set(CMAKE_CXX_STANDARD 20)

# list all sources
file(
        GLOB_RECURSE
        SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})