cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Pong)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Pong src/main.cpp src/config.cpp src/game.cpp src/renderer.cpp src/controller.cpp src/movingobject.cpp src/paddle.cpp src/ball.cpp)
target_link_libraries(Pong ${SDL2_LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/pong.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})