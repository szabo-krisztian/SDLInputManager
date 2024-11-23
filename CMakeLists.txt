cmake_minimum_required(VERSION 3.10)
project(Input_Manager_Project)

set(CMAKE_C_COMPILER "C:/ProgramData/mingw64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/ProgramData/mingw64/mingw64/bin/g++.exe")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 CONFIG REQUIRED)

add_executable(Main main.cpp)

add_subdirectory(input-manager)
add_subdirectory(demo-app)

target_link_libraries(Main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    DemoApp
)
