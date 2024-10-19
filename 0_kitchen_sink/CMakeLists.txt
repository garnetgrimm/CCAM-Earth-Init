cmake_minimum_required(VERSION 3.14)

project(kitchen_sink VERSION 0.0.1)

add_executable(kitchen_sink main.cpp)

target_link_libraries(kitchen_sink daisy)
target_link_libraries(kitchen_sink DaisySP)
target_link_libraries(kitchen_sink DaisySP_LGPL)
target_link_libraries(kitchen_sink ccam_json)