cmake_minimum_required(VERSION 3.29)
project(realm-of-spells-launcher)

set(CMAKE_CXX_STANDARD 20)

# Qt packages
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

# setup sources directories
set(FORMS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/forms)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# list all sources
file(
        GLOB_RECURSE
        SOURCES
        ${FORMS_DIR}/*.ui
        ${SOURCE_DIR}/*.cpp
        ${SOURCE_DIR}/*.h
        ${SOURCE_DIR}/*/*.cpp
        ${SOURCE_DIR}/*/*.h
)

# add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# add the executable based on platform
if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            Qt6::Widgets
)

# adding all the source directories to include path
target_include_directories( ${PROJECT_NAME}
        PRIVATE
            ${FORMS_DIR}
            ${SOURCE_DIR}
            ${SOURCE_DIR}
)