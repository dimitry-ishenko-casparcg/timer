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

set(GUI_LABEL       gui/label.cpp gui/label.hpp)
set(GUI_MAIN_WINDOW gui/main_window.cpp gui/main_window.hpp gui/main_window.ui)
set(GUI_TIME_WIDGET gui/time_widget.cpp gui/time_widget.hpp gui/time_widget.ui)
set(MAIN            src/main.cpp)
set(RESOURCES       res/resources.qrc)
set(SRC_CLOCK       src/clock.cpp src/clock.hpp)
set(SRC_TIME        src/time.hpp)

########################
# executable
add_executable(${PROJECT_NAME}
    ${GUI_LABEL}
    ${GUI_MAIN_WINDOW}
    ${GUI_TIME_WIDGET}
    ${MAIN}
    ${RESOURCES}
    ${SRC_CLOCK}
    ${SRC_TIME}
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
