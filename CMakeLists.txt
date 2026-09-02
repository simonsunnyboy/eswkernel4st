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

    # disable strange gcc assumptions
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

    # select Atari ST cross compiler and enable assembly language source files
    enable_language("ASM")

    set(CMAKE_C_COMPILER m68k-atari-mint-gcc)
    set(CMAKE_ASM_COMPILER m68k-atari-mint-as)
    set(CMAKE_AR m68k-atari-mint-ar)
    set(CMAKE_RANLIB m68k-atari-mint-ranlib)
    set(CMAKE_C_FLAGS "-m68000 -O3 -fomit-frame-pointer -Wextra -Wall -mshort -nostdlib -std=c99")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_C_FLAGS} ${ESWKERNEL4ST_TEST_SRC}/startup.S" )

    # include directories for assembly sources
    set(CMAKE_ASM_FLAGS "-m68000 -I${ESWKERNEL4ST_SRC}")

    set(ESWKERNEL4ST_ENABLE_TEST ON)
else()
    # project is already defined, test is not needed
    set(ESWKERNEL4ST_ENABLE_TEST OFF)
endif()

include_directories(${ESWKERNEL4ST_INCLUDE})

add_subdirectory(src)

if(ESWKERNEL4ST_ENABLE_TEST)
    message(STATUS "ESWKernel4ST_ENABLE_TEST is ON, adding test executables")
    add_subdirectory(test)
endif()