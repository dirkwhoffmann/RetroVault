target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        Controller.cpp
        CustomController.cpp
        BlockViewController.cpp
        DevicePanelController.cpp
        SplashPanelController.cpp
        SidebarController.cpp
        SidebarModel.cpp
        VolumePanelController.cpp
        WindowController.cpp)
