cmake_minimum_required(VERSION 3.10)
project(ShoppingBehaviourSimulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Discover all source files
file(GLOB_RECURSE SOURCES
    "core/*.cpp"
    "agents/*.cpp"
    "simulation/*.cpp"
    "analytics/*.cpp"
    "main.cpp"
)

# Replace any existing executable name (optional)
# But here we just build `simulator`
add_executable(simulator ${SOURCES})
