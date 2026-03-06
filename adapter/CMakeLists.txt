target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        BlockTableModel.cpp
        SidebarModel.cpp
        UsageDisplay.cpp
        QmlAdapterTypes.cpp
        QmlAdapter.cpp)
