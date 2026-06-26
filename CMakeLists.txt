cmake_minimum_required(VERSION 2.8)

project(ESWKernel4ST)
# disable strange gcc assumptions
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# define some directories
set(KERNEL_SRC ${PROJECT_SOURCE_DIR}/src)
set(TEST_SRC ${PROJECT_SOURCE_DIR}/test)


# select Atari ST cross compiler and enable assembly language source files
enable_language("ASM")

set(CMAKE_C_COMPILER m68k-atari-mint-gcc)
set(CMAKE_ASM_COMPILER m68k-atari-mint-as)
set(CMAKE_AR m68k-atari-mint-ar)
set(CMAKE_RANLIB m68k-atari-mint-ranlib)
set(CMAKE_C_FLAGS "-m68000 -O3 -fomit-frame-pointer -Wextra -Wall -mshort -nostdlib -std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_C_FLAGS} ${TEST_SRC}/startup.S" )

# include directories for assembly sources
set(CMAKE_ASM_FLAGS "-m68000 -I${KERNEL_SRC}")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(eswkernel4st
	${KERNEL_SRC}/main.c
	${KERNEL_SRC}/cookie.c
	${KERNEL_SRC}/screen.c
	${KERNEL_SRC}/picture.c
	${KERNEL_SRC}/interrupt_handlers.c
	${KERNEL_SRC}/decode_pc1.S
	${KERNEL_SRC}/interrupt.S
	${KERNEL_SRC}/jagpad.S
	${KERNEL_SRC}/ikbd_isr.S
	${KERNEL_SRC}/ikbd_joy.c
	${KERNEL_SRC}/ikbd_keyb.c
	${KERNEL_SRC}/ikbd_mouse.c
	${KERNEL_SRC}/reset.S
	${KERNEL_SRC}/leonard.S
	README.md
	LICENSE
)

add_executable(demo_isr.tos
	${TEST_SRC}/demo_isr.c
)

target_link_libraries(demo_isr.tos eswkernel4st)

add_executable(demo_pc1.tos
	${TEST_SRC}/demo_pc1.c
	${TEST_SRC}/demo_pc1.h
)

target_link_libraries(demo_pc1.tos eswkernel4st)
