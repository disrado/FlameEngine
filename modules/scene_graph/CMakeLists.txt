cmake_minimum_required(VERSION 3.10)

project(scene_graph LANGUAGES CXX)

set(${PROJECT_NAME}_HEADERS
    include/scene_graph/Node.hpp
)

set(${PROJECT_NAME}_SOURCES
    src/Node.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)

add_library(flame::scene_graph ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /MP /W3 /Zf
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
            -Wall -Wextra -Werror -Wpedantic -pedantic-errors -pipe>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        util
        ecs
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
