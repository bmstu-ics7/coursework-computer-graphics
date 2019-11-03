cmake_minimum_required(VERSION 3.1.0)

project(clouds)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    "gui"
)

set(HEADERS
    include/Window/MainWindow.h
    include/Window/OpenGLWidget.h
    include/Commands/Command.h
    include/Commands/AddCamera.h
    include/Commands/Draw.h
    include/Commands/Load.h
    include/Commands/Offset.h
    include/Commands/Rotate.h
    include/Commands/Save.h
    include/Commands/Scale.h
    include/Drawing/Drawer.h
    include/Drawing/QtDraw.h
    include/Finder/File.h
    include/Managers/Manager.h
    include/Managers/DeleteManager.h
    include/Managers/DrawManager.h
    include/Managers/ExceptionManager.h
    include/Managers/FileManager.h
    include/Managers/TransformManager.h
    include/Math/Matrix.h
    include/Object/Builder.h
    include/Object/Camera.h
    include/Object/ComposeObject.h
    include/Object/Edge.h
    include/Object/Model.h
    include/Object/Object.h
    include/Object/Point2D.h
    include/Object/Point3D.h
    include/Object/Position.h
    include/Object/UnvisibleObject.h
    include/Object/VisibleObject.h
    include/Scene/Iterator.h
    include/Scene/Scene.h
    include/Scene/SceneContainer.h
)

set(SOURCES
    source/main.cc
    source/Window/MainWindow.cc
    source/Window/OpenGLWidget.cc
    source/Commands/Draw.cc
    source/Commands/Load.cc
    source/Commands/Offset.cc
    source/Commands/Rotate.cc
    source/Commands/Save.cc
    source/Commands/Scale.cc
    source/Drawing/QtDraw.cc
    source/Finder/File.cc
    source/Managers/DrawManager.cc
    source/Managers/FileManager.cc
    source/Managers/TransformManager.cc
    source/Object/Builder.cc
    source/Object/Model.cc
    source/Object/Point2D.cc
    source/Object/Point3D.cc
    source/Object/Position.cc
    source/Object/Camera.cc
    source/Scene/SceneContainer.cc
    source/Math/Matrix.cc
)

set(GUI
    gui/MainWindow.ui
)

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
