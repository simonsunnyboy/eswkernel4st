#
# Entertainment Software Kernel for Atari ST
# (c) 2016/18/26 by Matthias Arndt / ASM Software
#
# The MIT License applies to this software. Refer to the file COPYING for
# details.
#
# test/CMakeLists.txt for test programs
#

# test programs use test/startup.S as the startup code
# Reuse is allowed.

add_executable(demo_isr.tos
	demo_isr.c
)

target_link_libraries(demo_isr.tos eswkernel4st)

add_executable(demo_pc1.tos
	demo_pc1.c
	demo_pc1.h
)

target_link_libraries(demo_pc1.tos eswkernel4st)
