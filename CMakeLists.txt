set(CMAKE_TOOLCHAIN_FILE libDaisy/cmake/toolchains/stm32h750xx.cmake)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.20)
project(ccam_eurorack VERSION 1.0.0)

set(LIBDAISY_DIR libDaisy)
set(DIASYSP_DIR DaisySP)
set(USE_DAISYSP_LGPL 1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(DaisySP)
add_subdirectory(DaisySP/DaisySP-LGPL)
add_subdirectory(libDaisy)

add_subdirectory(json)
add_subdirectory(0_kitchen_sink)