cmake_minimum_required(VERSION 3.16)
if (NOT NOCMAKE)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
endif()
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
project(conplay LANGUAGES CXX VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-D__cpp_lib_is_invocable)
include_directories(include)
link_directories(lib)
aux_source_directory(src SRC)
add_executable(conplay ${SRC})
target_link_libraries(conplay bass)
