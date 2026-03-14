target_include_directories(retrovault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(retrovault PRIVATE
        ColorBar.cpp
        CustomComponent.cpp
        Scanner.cpp)
