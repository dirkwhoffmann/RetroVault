cmake_minimum_required(VERSION 4.1)
project(retrovault)

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

add_executable(retrovault
        main.cpp
        backend.cpp
        backend.h)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(retrovault
        URI retrovaultUI
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
            assets/github.png
            assets/fonts/SourceSans3-VariableFont_wght.ttf)

target_link_libraries(retrovault PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Gui
        Qt6::QuickControls2
        Qt6::QuickDialogs2)

