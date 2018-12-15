cmake_minimum_required(VERSION 3.10)

project(logger LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES 
    "src/*.cpp"
)

add_library(${PROJECT_NAME}
    STATIC
        ${${PROJECT_NAME}_SOURCES}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			/MP /W3 /Zf
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -Werror -Wpedantic -pedantic-errors -pipe -pthread -fPIC>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
)