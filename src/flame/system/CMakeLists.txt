cmake_minimum_required(VERSION 3.10)

project(system LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(HEADERS_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../include)
set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/)


set(${PROJECT_NAME}_HEADERS
    ${HEADERS_DIR}/flame/system/Vector2.hpp
    ${HEADERS_DIR}/flame/system/Vector2.inl
)


set(${PROJECT_NAME}_SOURCES
    ${SOURCES_DIR}/main.cpp
)

add_library(${PROJECT_NAME}
    SHARED
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${SDL2_LIBRARY}
        ${CONAN_LIBS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        ${CONAN_LIBS}
)