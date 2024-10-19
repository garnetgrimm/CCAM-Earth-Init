cmake_minimum_required(VERSION 3.20)
project(ccam_json VERSION 1.0.0)

file(GLOB jsonFiles *.json)

set(headerFiles "")
foreach(file_json ${jsonFiles})
    get_filename_component(file_h ${file_json} NAME_WE)
    set(file_h ${CMAKE_CURRENT_BINARY_DIR}/${file_h}.h)
    add_custom_command(
            OUTPUT ${file_h}
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/json2daisy/src"
            COMMAND python -m json2daisy ${file_json} -o ${file_h}
    )
    list(APPEND headerFiles ${file_h})
endforeach()

add_custom_target(board_defs ALL DEPENDS ${headerFiles})

add_library(ccam_json INTERFACE)
target_include_directories(ccam_json INTERFACE ${CMAKE_BINARY_DIR}/json)
add_dependencies(ccam_json board_defs)