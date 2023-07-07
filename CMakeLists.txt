cmake_minimum_required(VERSION 3.20)

project(simple-graphic)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SIMPLE_GRAPHIC_SOURCES "engine/*.c" "engine/*.cpp")
file(GLOB_RECURSE SIMPLE_GRAPHIC_HEADERS "engine/*.h")

add_library(simple-graphic ${SIMPLE_GRAPHIC_SOURCES} ${SIMPLE_GRAPHIC_HEADERS})
target_include_directories(simple-graphic PRIVATE "engine" ${CMAKE_SOURCE_DIR})
target_compile_options(simple-graphic PRIVATE "-Wfatal-errors")

if (NOT MSVC)
    target_link_libraries(simple-graphic PRIVATE "glfw3")
endif()