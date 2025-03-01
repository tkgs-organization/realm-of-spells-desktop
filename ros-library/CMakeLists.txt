cmake_minimum_required(VERSION 3.29)
project(realm-of-spells-library)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# libcurl (cURLpp dependency)
find_package(CURL REQUIRED)

# cURLpp itself
FetchContent_Declare(
        curlpp
        GIT_REPOSITORY https://github.com/jpbarrette/curlpp
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(curlpp)

# nlohmann JSON
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Specify include directories for the library
target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ${CURL_LIBRARIES}
            curlpp
            nlohmann_json::nlohmann_json
)
