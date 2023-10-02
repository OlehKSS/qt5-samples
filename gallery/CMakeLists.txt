cmake_minimum_required(VERSION 3.22.0)

project(gallery VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(gallery_PATH "PATH=%PATH%" "$ENV{Qt5_PATH}")
endif()

find_package(Qt5 COMPONENTS Widgets Charts Sql REQUIRED)

add_subdirectory(core)
add_subdirectory(desktop)
