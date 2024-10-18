cmake_minimum_required(VERSION 3.14)

project(kitchen_sink VERSION 0.0.1)
target_link_libraries(${target} board_defs)

add_executable(KitchenSink main.cpp)