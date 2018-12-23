cmake_minimum_required(VERSION 3.10)

project(graphics LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(HEADERS_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../include)
set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/)

set(${PROJECT_NAME}_SOURCES
	${SOURCES_DIR}/main.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${SDL2_LIBRARY}
        ${CONAN_LIBS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${HEADERS_DIR}
        ${CONAN_LIBS}
)