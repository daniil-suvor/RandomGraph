cmake_minimum_required (VERSION 3.12)

project(matrix_graph)

file(GLOB HEADER "src/*.h")
file(GLOB SRC "src/*.cpp")

add_subdirectory(iterator)

add_library(${PROJECT_NAME} STATIC ${HEADER} ${SRC})

target_link_libraries(${PROJECT_NAME} iterator)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
