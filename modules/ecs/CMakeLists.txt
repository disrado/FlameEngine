cmake_minimum_required(VERSION 3.10)

project(ecs LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/*.cpp")

add_library(${PROJECT_NAME}
    SHARED
        ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${CONAN_LIBS}
        types
        utils
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        ${CONAN_LIBS}
)