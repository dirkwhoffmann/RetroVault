cmake_minimum_required(VERSION 4.1)
project(vBoard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Quick
        Gui
        QuickControls2
        QuickDialogs2
        REQUIRED)

add_executable(vBoard
        main.cpp
        backend.cpp
        backend.h)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(vBoard
        URI vBoardUI
        VERSION 1.0
        QML_FILES
            main.qml
            SplashView.qml
            MainTableView.qml
        RESOURCES
            assets/AppIcon.png
            assets/splash.png
            assets/LEDred.png
            assets/LEDgreen.png
            assets/github.png)

target_link_libraries(vBoard PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Gui
        Qt6::QuickControls2
        Qt6::QuickDialogs2)

