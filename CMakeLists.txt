#
# Entertainment Software Kernel for Atari ST
# (c) 2016/18/26 by Matthias Arndt / ASM Software
#
# The MIT License applies to this software. Refer to the file COPYING for
# details.
#
# top-level CMakeLists.txt as entry point
#

cmake_minimum_required(VERSION 2.8)

# define some directories
set(ESWKERNEL4ST_SRC ${CMAKE_CURRENT_LIST_DIR}/src)
set(ESWKERNEL4ST_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)
set(ESWKERNEL4ST_TEST_SRC ${CMAKE_CURRENT_LIST_DIR}/test)

# Check if the PROJECT_NAME variable is defined
# only use a certain compiler and linker configuration if the project name is not defined yet
if(NOT DEFINED PROJECT_NAME)
    project(ESWKernel4ST)

    # configure variables for use with compilation toolchain for test executables
    set(ATARI_ASM_INCLUDE "${ESWKERNEL4ST_SRC}" CACHE PATH "")
    set(ATARI_STARTUP_FILE "${ESWKERNEL4ST_TEST_SRC}/startup.S" CACHE FILEPATH "")

    # include toolchain
    include(${CMAKE_CURRENT_LIST_DIR}/m68k-atari-mint.cmake)

    set(ESWKERNEL4ST_ENABLE_TEST ON)
else()
    # project is already defined, test is not needed
    set(ESWKERNEL4ST_ENABLE_TEST OFF)
endif()

include_directories(${ESWKERNEL4ST_INCLUDE})

add_subdirectory(src)

if(ESWKERNEL4ST_ENABLE_TEST)
    message(STATUS "ESWKERNEL4ST_ENABLE_TEST is ON, adding test executables")
    add_subdirectory(test)
endif()