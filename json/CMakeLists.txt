cmake_minimum_required(VERSION 3.20)
project(ccam_json VERSION 1.0.0)

file(GLOB jsonFiles *.json)

foreach(file_json ${jsonFiles})
    get_filename_component(file_h ${file_json} NAME_WE)
    set(file_h "${file_h}.h")
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gen/${file_h}
            COMMAND $(PYTHONPATH):json2daisy/src python -m json2daisy ${file_json}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gen/${file_h}
    )
    message(${CMAKE_CURRENT_SOURCE_DIR}/${file_h})
endforeach()

string(REGEX REPLACE jsonFiles "[.]json$" ".h" headerFiles ${jsonFiles})
add_library(board_defs ${headerFiles})