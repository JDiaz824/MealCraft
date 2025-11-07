cmake_minimum_required(VERSION 3.10)
project(MealCraft)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/Users/asian/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/data-structures/*.cpp
    frontend/*.cpp
)

add_executable(MealCraft 
    ${SOURCES}
)

target_include_directories(MealCraft PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/data-structures
    ${PROJECT_SOURCE_DIR}/frontend
)

target_link_libraries(MealCraft PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
)
