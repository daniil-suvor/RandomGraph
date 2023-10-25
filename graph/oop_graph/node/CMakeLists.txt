cmake_minimum_required (VERSION 3.12)

project(node)

file(GLOB HEADER "src/*.h")
file(GLOB SRC "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${HEADER} ${SRC})

#target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)