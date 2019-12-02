cmake_minimum_required(VERSION 3.1.0)

project(clouds)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC_SEARCH_PATHS
#    "gui"
#)

set(HEADERS
    include/Widget/Widget.h
    include/Particle.h
    include/Noise/TileableVolumeNoise.h
    include/Noise/PerlinNoise.hpp
)

set(SOURCES
    source/main.cc
    source/Widget/Draw.cc
    source/Widget/Control.cc
    source/Widget/Camera.cc
    source/Particle.cc
    source/Noise/TileableVolumeNoise.cc
)

#set(GUI
#    gui/MainWindow.ui
#)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL)

add_executable(clouds
    ${HEADERS}
    ${SOURCES}
    ${GUI}
)

target_include_directories(clouds
    PUBLIC
        "include"
)

target_link_libraries(clouds Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})
