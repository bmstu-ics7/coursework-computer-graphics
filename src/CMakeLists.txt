cmake_minimum_required(VERSION 3.1.0)

project(clouds)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    "gui"
)

set(GUI
    gui/mainwindow.ui
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SHADERS "shaders/*.[vf]sh")

set(HEADERS
    include/Widget/MainWindow.h
    include/Widget/Widget.h
    include/Objects/Particle.h
    include/Objects/SkyBox.h
    include/Noise/TileableVolumeNoise.h
    include/Noise/PerlinNoise.hpp
)

set(SOURCES
    source/main.cc
    source/Widget/MainWindow.cc
    source/Widget/Draw.cc
    source/Widget/Control.cc
    source/Widget/Camera.cc
    source/Objects/Particle.cc
    source/Objects/SkyBox.cc
    source/Noise/TileableVolumeNoise.cc
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL)

add_executable(clouds
    ${SHADERS}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(clouds
    PUBLIC
        "include"
        "include/glm"
)

target_link_libraries(clouds Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})
