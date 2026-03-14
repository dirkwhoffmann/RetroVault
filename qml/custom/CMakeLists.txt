target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        BaseScanner.cpp
        ColorBar.cpp
        CustomComponent.cpp
        HealthScanner.cpp
        Scanner.cpp
        UsageScanner.cpp)
