#
# Entertainment Software Kernel for Atari ST
# (c) 2016/18/26 by Matthias Arndt / ASM Software
#
# The MIT License applies to this software. Refer to the file COPYING for
# details.
#
# src/CMakeLists.txt for actual kernel library
#

# user program configuration (use before including this CMakeLists.txt	):
# set(ESWK_ENABLE_IKBD_HANDLER OFF CACHE BOOL "Disable IKBD subsystem")

# defaults for building the library
option(ESWK_ENABLE_SCREENBUFFER "Enable screen buffer initialization" ON)
option(ESWK_ENABLE_IKBD_HANDLER "Enable IKBD handler" ON)

# source filesd always to be included:
set(ESWK_SOURCES
	main.c
	cookie.c
	screen.c
	picture.c
	interrupt_handlers.c
	decode_pc1.S
	interrupt.S
	jagpad.S
	reset.S
	leonard.S
)

# source files depending on configuration options:
if(ESWK_ENABLE_SCREENBUFFER)
	message(STATUS "ESWK_ENABLE_SCREENBUFFER is ON: screen buffer initialization will be compiled into the kernel")
    list(APPEND ESWK_SOURCES screen_buffer.c)
endif()

if(ESWK_ENABLE_IKBD_HANDLER)
	message(STATUS "ESWK_ENABLE_IKBD_HANDLER is ON: IKBD handler will be compiled into the kernel")
	list(APPEND ESWK_SOURCES 
		ikbd_isr.S
		ikbd_joy.c
		ikbd_keyb.c
		ikbd_mouse.c
	)
endif()

# the actual library target to build:
add_library(eswkernel4st ${ESWK_SOURCES})