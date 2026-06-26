#
# Entertainment Software Kernel for Atari ST
# (c) 2016/18/26 by Matthias Arndt / ASM Software
#
# The MIT License applies to this software. Refer to the file COPYING for
# details.
#
# src/CMakeLists.txt for actual kernel library
#

add_library(eswkernel4st
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
