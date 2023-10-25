cmake_minimum_required (VERSION 3.12)

project(iterator)

file(GLOB HEADER "src/*.h")
file(GLOB SRC "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${HEADER} ${SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
