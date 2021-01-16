cmake_minimum_required(VERSION 3.17)

project(SelectOpenCVSettings LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get the JsonCpp library
include(FetchContent)
#FetchContent_Declare(
#    jsoncpp
#    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
#    GET_TAG master
#)
FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(jsoncpp)

# Find Qt6
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Find OpenCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(SelectOpenCVSettings
    ${PROJECT_SOURCES}
)
target_link_libraries(SelectOpenCVSettings
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE ${OpenCV_LIBS}
    PRIVATE jsoncpp_static
)
