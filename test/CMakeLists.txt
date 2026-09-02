#
# Entertainment Software Kernel for Atari ST
# (c) 2016/18/26 by Matthias Arndt / ASM Software
#
# The MIT License applies to this software. Refer to the file COPYING for
# details.
#
# test/CMakeLists.txt for test programs
#

# Define a macro to create an Atari ST executable with startup.S included first
macro(add_atari_executable TARGET)
    # Remaining arguments are the source files
    set(_sources ${ARGN})

    # Prepend startup.S (must be first)
    add_executable(${TARGET}
        ${CMAKE_CURRENT_LIST_DIR}/startup.S
        ${_sources}
    )

    # Always link against the kernel library
    target_link_libraries(${TARGET} eswkernel4st)
endmacro()


add_atari_executable(demo_isr.tos
	demo_isr.c
)

add_atari_executable(demo_pc1.tos
	demo_pc1.c
	demo_pc1.h
)
