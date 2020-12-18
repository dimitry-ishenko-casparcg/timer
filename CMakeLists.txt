cmake_minimum_required(VERSION 3.1)
project(timer VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Network Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(GUI_CLOCK_WIDGET gui/clock_widget.cpp gui/clock_widget.hpp)
set(GUI_CUSTOM       gui/custom.hpp)
set(GUI_EVENT_WIDGET gui/event_widget.cpp gui/event_widget.hpp gui/event_widget.ui)
set(GUI_LABEL        gui/label.cpp gui/label.hpp)
set(GUI_MAIN_WINDOW  gui/main_window.cpp gui/main_window.hpp gui/main_window.ui)
set(GUI_TIME_WIDGET  gui/time_widget.cpp gui/time_widget.hpp gui/time_widget.ui)
set(GUI_VIDEO_WIDGET gui/video_widget.cpp gui/video_widget.hpp gui/video_widget.ui)
set(MAIN             src/main.cpp)
set(OSC_SERVER       osc/server.cpp osc/server.hpp)
set(RESOURCES        res/resources.qrc)
set(SRC_CLOCK        src/clock.cpp src/clock.hpp)
set(SRC_RANGE        src/range.hpp)
set(SRC_TIME         src/time.hpp)

########################
# executable
add_executable(${PROJECT_NAME}
    ${GUI_CLOCK_WIDGET}
    ${GUI_CUSTOM}
    ${GUI_EVENT_WIDGET}
    ${GUI_LABEL}
    ${GUI_MAIN_WINDOW}
    ${GUI_TIME_WIDGET}
    ${GUI_VIDEO_WIDGET}
    ${MAIN}
    ${OSC_SERVER}
    ${RESOURCES}
    ${SRC_CLOCK}
    ${SRC_RANGE}
    ${SRC_TIME}
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Widgets osc++)

########################
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES LICENSE.md README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

########################
set(CPACK_STRIP_FILES ON)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Timer application for CasparCG")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Dimitry Ishenko <dimitry (dot) ishenko (at) (gee) mail (dot) com>")

set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
