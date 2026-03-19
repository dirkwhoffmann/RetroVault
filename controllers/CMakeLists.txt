target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        AppController.cpp
        Controller.cpp
        CustomController.cpp
        DevicePanelController.cpp
        SplashPanelController.cpp
        SidebarController.cpp
        VolumePanelController.cpp
        WindowController.cpp)
