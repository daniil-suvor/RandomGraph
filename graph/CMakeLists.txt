cmake_minimum_required (VERSION 3.12)

project(graph)

file(GLOB HEADER "src/*.h")
file(GLOB SRC "src/*.cpp")

add_subdirectory(oop_graph)
add_subdirectory(matrix_graph)

find_package(OpenMP REQUIRED)

add_library(${PROJECT_NAME} STATIC ${HEADER} ${SRC})
target_link_libraries(${PROJECT_NAME} oop_graph matrix_graph OpenMP::OpenMP_CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
