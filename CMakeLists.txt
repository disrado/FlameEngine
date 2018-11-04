cmake_minimum_required(VERSION 3.10)

project(arena LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(conan)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/extern)

add_subdirectory(extern/libpqxx)
add_subdirectory(extern/timer)
add_subdirectory(modules/db)
add_subdirectory(modules/graphics)
add_subdirectory(modules/system)

if (ENABLE_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif ()