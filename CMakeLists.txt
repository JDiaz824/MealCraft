cmake_minimum_required(VERSION 3.10)

# Project name
project(MealCraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/data-structures/*.cpp
)

# Create the executable
add_executable(MealCraft ${SOURCES})

# Include directories for headers
target_include_directories(MealCraft PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/data-structures
)
