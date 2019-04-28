cmake_minimum_required(VERSION 3.10)

project(tests LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(GLOB VISUAL_TEST_SRC "VisualTest.cpp")

add_executable(VisualTest
    ${VISUAL_TEST_SRC}
)

target_compile_features(VisualTest PUBLIC cxx_std_17)

target_link_libraries(VisualTest
    PUBLIC
        ${CONAN_LIBS}
        system
        graphics
)

target_include_directories(VisualTest
    PUBLIC
        include
        ${CONAN_LIBS}
)

function(create_test name library)
    add_executable(${name} ${name}.cpp)

    target_include_directories(${name}
        PUBLIC
            ${CONAN_LIBS}
    )

    target_link_libraries(${name}
        PUBLIC
            ${SDL2_LIBRARY}
            ${CONAN_LIBS}
            ${library}
    )
    
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()

create_test(Vector2_Test system)