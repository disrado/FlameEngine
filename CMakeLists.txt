cmake_minimum_required(VERSION 3.10)

project(flame LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(conan)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

add_subdirectory(external/libpqxx)
add_subdirectory(modules/flame/utils)
add_subdirectory(modules/flame/db)
add_subdirectory(modules/flame/graphics)
add_subdirectory(modules/flame/system)

if (ENABLE_TESTING)
	enable_testing()
endif ()