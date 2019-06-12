cmake_minimum_required(VERSION 3.10)

project(tests LANGUAGES CXX)

function(create_test name file library)
    add_executable(${name} ${file})

    target_compile_features(${name} PUBLIC cxx_std_17)

    target_include_directories(${name}
        PUBLIC
            ${CONAN_LIBS}
    )

    target_link_libraries(${name}
        PUBLIC
            ${CONAN_LIBS}
            ${library}
    )
    
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()

create_test(EntityTest       ecs/EntityTest.cpp          ecs)
create_test(Vector2Test      system/Vector2Test.cpp      system)
create_test(IdGenerationTest util/IdGenerationTest.cpp   util)