cmake_minimum_required(VERSION 3.20)

project(GameVision LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv5)

add_executable(GameVision
    src/main.cpp
)

target_link_libraries(GameVision PRIVATE
    PkgConfig::OPENCV
    user32
    gdi32
)

if(MINGW)
    target_link_options(GameVision PRIVATE -static-libgcc -static-libstdc++)
endif()
