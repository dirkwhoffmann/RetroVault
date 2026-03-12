target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        CustomComponent.cpp
        BaseScanner.cpp
        UsageDisplay.cpp
        UsageScanner.cpp)
