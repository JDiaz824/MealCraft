cmake_minimum_required(VERSION 3.10)

# Project name
project(MealCraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add SFML and ImGui-SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
add_subdirectory(frontend/imgui-sfml)

# Define source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/data-structures/*.cpp
    frontend/*.cpp
    frontend/imgui/*.cpp   # Add ImGui core .cpp files manually here
)

# Create the executable
add_executable(MealCraft 
    ${SOURCES}
)


# Include directories for headers
target_include_directories(MealCraft PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/data-structures
    ${PROJECT_SOURCE_DIR}/frontend
    ${PROJECT_SOURCE_DIR}/frontend/imgui
    ${PROJECT_SOURCE_DIR}/frontend/imgui-sfml
)

# Link libraries
target_link_libraries(MealCraft PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    ImGui-SFML::ImGui-SFML
)