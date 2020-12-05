cmake_minimum_required(VERSION 3.1)
project(timer VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(GUI
    gui/main_window.cpp
    gui/main_window.hpp
    gui/main_window.ui
)
set(SRC
    src/main.cpp
)

########################
# executable
add_executable(${PROJECT_NAME} ${GUI} ${SRC})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
