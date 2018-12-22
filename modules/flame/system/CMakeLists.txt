cmake_minimum_required(VERSION 3.10)

project(system LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES 
    "src/*.cpp"
    "src/*.inl"
)

add_library(${PROJECT_NAME}
    SHARED
        ${${PROJECT_NAME}_SOURCES}
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