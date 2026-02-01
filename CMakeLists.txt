cmake_minimum_required(VERSION 3.10)
project(sistema-bancario)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(sistema-bancario ${SOURCES})

# Compiler flags
if(MSVC)
    target_compile_options(sistema-bancario PRIVATE /W4)
else()
    target_compile_options(sistema-bancario PRIVATE -Wall -Wextra -Wpedantic)
endif()
