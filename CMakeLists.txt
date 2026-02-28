cmake_minimum_required(VERSION 4.1)
project(rvlib)

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
        QuickEffects
        REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse)

add_subdirectory(utlib)
add_subdirectory(rvlib)

add_executable(retrovault
        backend.cpp
        debug.cpp
        FuseDevice.cpp
        FuseMountPoint.cpp
        FuseVolume.cpp
        main.cpp
)

target_include_directories(retrovault PRIVATE
        utlib
        rvlib
        /usr/local/include)

target_link_libraries(retrovault PRIVATE
        utlib
        rvlib
        Qt6::Core
        Qt6::Quick
        Qt6::Gui
        Qt6::QuickControls2
        Qt6::QuickDialogs2
        Qt6::QuickEffects)

target_include_directories(retrovault PRIVATE ${FUSE_INCLUDE_DIRS})
target_link_libraries(retrovault PRIVATE ${FUSE_LIBRARIES})
target_compile_options(retrovault PRIVATE ${FUSE_CFLAGS_OTHER})

#target_compile_definitions(retrovault PRIVATE
#        _FILE_OFFSET_BITS=64)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_add_qml_module(retrovault

        URI retrovaultUI
        VERSION 1.0

        QML_FILES
        qml/DevicePanel.qml
        qml/main.qml
        qml/Sidebar.qml
        qml/SplashView.qml
        qml/MainTableView.qml

        RESOURCES
        assets/AppIcon.png
        assets/splash.png
        assets/LEDred.png
        assets/LEDgreen.png
        assets/github.png
        assets/fonts/SourceSans3-VariableFont_wght.ttf)
