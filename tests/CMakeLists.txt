cmake_minimum_required(VERSION 3.10)

project(tests LANGUAGES CXX)

file(GLOB VISUAL_TEST_SRC "VisualTest.cpp")

function(create_test name file library)
    add_executable(${name} ${file})

    target_compile_features(${name} PUBLIC cxx_std_17)

    target_include_directories(${name}
        PRIVATE
            ${CONAN_LIBS}
    )

    target_link_libraries(${name}
        PRIVATE
            ${CONAN_LIBS}
            ${library}
    )
    
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()

create_test(EntityTest ecs/EntityTest.cpp ecs)
