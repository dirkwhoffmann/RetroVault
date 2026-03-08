target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        Controller.cpp
        BlockViewController.cpp
        DevicePanelController.cpp
        SplashPanelController.cpp
        SidebarController.cpp
        SidebarModel.cpp
        WindowController.cpp)
