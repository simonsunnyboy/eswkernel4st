#
# Entertainment Software Kernel for Atari ST
# (c) 2016/18/26 by Matthias Arndt / ASM Software
#
# The MIT License applies to this software. Refer to the file COPYING for
# details.
#
# src/CMakeLists.txt for actual kernel library
#

option(ESWK_ENABLE_SCREENBUFFER "Enable screen buffer initialization" ON)

set(ESWK_SOURCES
	main.c
	cookie.c
	screen.c
	picture.c
	interrupt_handlers.c
	decode_pc1.S
	interrupt.S
	jagpad.S
	ikbd_isr.S
	ikbd_joy.c
	ikbd_keyb.c
	ikbd_mouse.c
	reset.S
	leonard.S
)

if(ESWK_ENABLE_SCREENBUFFER)
	message(STATUS "ESWK_ENABLE_SCREENBUFFER is ON: screen buffer initialization will be compiled into the kernel")
    list(APPEND ESWK_SOURCES screen_buffer.c)
endif()

add_library(eswkernel4st ${ESWK_SOURCES})