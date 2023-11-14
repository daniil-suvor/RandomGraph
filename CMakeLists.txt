cmake_minimum_required (VERSION 3.12)

project (RandomGraph)

add_subdirectory(graph)

add_executable(main main.cpp)
target_link_libraries(main graph)
set_property(TARGET main PROPERTY CXX_STANDARD 20)