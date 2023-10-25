cmake_minimum_required (VERSION 3.12)

project(oop_graph)

file(GLOB HEADER "src/*.h")
file(GLOB SRC "src/*.cpp")

add_subdirectory(node)

add_library(${PROJECT_NAME} STATIC ${HEADER} ${SRC})
target_link_libraries(${PROJECT_NAME} node)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
