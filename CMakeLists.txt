cmake_minimum_required(VERSION 3.21)

project(OpenLoad
    VERSION 0.1.0
    DESCRIPTION "Open-source desktop download manager"
    HOMEPAGE_URL "https://github.com/tehsaad/OpenLoad"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(OPENLOAD_BUILD_TESTS "Build the automated test suite" ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Widgets Svg Concurrent)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
    add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)

if(OPENLOAD_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation layout shared by the Linux package and the Windows installer.
include(GNUInstallDirs)
install(TARGETS openload RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(UNIX AND NOT APPLE)
    include(packaging/linux/LinuxPackaging.cmake)
endif()
