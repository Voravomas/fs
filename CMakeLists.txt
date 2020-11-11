cmake_minimum_required(VERSION 3.15)
project(fs
        VERSION 1.0.0
        DESCRIPTION "FAT-16 reader"
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Options
option(WARNINGS_AS_ERRORS   "Treat compiler warnings as errors."    OFF)
option(ENABLE_CONAN         "Use Conan as a package manager."       OFF)
option(ENABLE_PVS_STUDIO    "Use PVS-Studio static code analyzer."  OFF) # Option for the local usage only. PVS-Studio isn't installed on GitHub machines.
option(ENABLE_SANITIZERS    "Use sanitizers to detect errors."      OFF) # Option for the test builds. Do not use it in the production builds.

# Project source compilation
add_executable(fs src/main.cpp src/printer.cpp header/printer.h header/structs.h src/helper.cpp header/helper.h)

# Add external packages
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(fs Boost::program_options)

# Include default CMake configuration
include(cmake/Config.cmake)
