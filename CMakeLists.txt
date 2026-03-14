cmake_minimum_required(VERSION 4.1)
project(retrovault)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Concurrent
        Gui
        Quick
        QuickControls2
        QuickDialogs2
        QuickEffects
        REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse)

add_executable(retrovault
        Assets.cpp
        debug.cpp
        main.cpp)

add_subdirectory(utlib)
add_subdirectory(rvlib)
add_subdirectory(controllers)
add_subdirectory(backend)
add_subdirectory(qml/custom)

target_include_directories(retrovault PRIVATE
        utlib
        rvlib
        /usr/local/include)

target_link_libraries(retrovault PRIVATE
        utlib
        rvlib
        Qt6::Core
        Qt6::Concurrent
        Qt6::Gui
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::QuickDialogs2
        Qt6::QuickEffects)

#
# FUSE
#

target_include_directories(retrovault PRIVATE
        ${FUSE_INCLUDE_DIRS})

target_link_libraries(retrovault PRIVATE
        ${FUSE_LIBRARIES})

target_compile_options(retrovault PRIVATE
        ${FUSE_CFLAGS_OTHER})

#
# Qt
#

qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

file(GLOB_RECURSE QML_SOURCES CONFIGURE_DEPENDS
        "qml/*.qml")

file(GLOB_RECURSE ASSET_RESOURCES CONFIGURE_DEPENDS
        "assets/fonts/*.ttf"
        "assets/icons/*.svg"
        "assets/icons/*.png"
        "assets/images/*.png")

list(TRANSFORM QML_SOURCES REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "")
list(TRANSFORM ASSET_RESOURCES REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "")

# Declare singletons
set_source_files_properties(qml/Style.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

# Add all files

qt_add_resources(retrovault "assets_files"
        PREFIX "/assets"
        BASE "assets"
        FILES ${ASSET_RESOURCES})

qt_add_qml_module(retrovault
        URI retrovaultUI
        VERSION 1.0
        QML_FILES ${QML_SOURCES})