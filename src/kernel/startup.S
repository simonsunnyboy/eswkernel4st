 |
 | Entertainment Software Kernel for Atari ST
 | (c) 2016/18/26 by Matthias Arndt / ASM Software
 |
 | The MIT License applies to this software. Refer to the file LICENSE for
 | details.
 |
 | @file  startup.S
 | @brief Basuic startup code for .TOS application that never returns
 | @details Based upon GNU as/gcc compatible startup code by mfro
 |
 |	
	
		
			.equ 	BASEPAGE_SIZE,0x100
			.equ	STACK_SIZE,0x4000
			.equ    MCH,0x5f4d4348
			.equ    CT60,0x43543630
					
			.text
			.globl ___main

start:
			move.l	4(sp),a5				| address to basepage
			move.l	0x0c(a5),d0				| length of text segment
			add.l	0x14(a5),d0				| length of data segment
			add.l	0x1c(a5),d0				| length of bss segment
			add.l	#STACK_SIZE+BASEPAGE_SIZE,d0		| length of stackpointer+basepage
			move.l	a5,d1					| address to basepage
			add.l	d0,d1					| end of program
			and.l	#0xfffffff0,d1			| align stack
			move.l	d1,sp					| new stackspace

			move.l	d0,-(sp)				| mshrink()
			move.l	a5,-(sp)
			clr.w	-(sp)
			move.w	#0x4a,-(sp)
			trap	#1
			lea.l	12(sp),sp
			
			jsr _main
			illegal                         | main() is not supposed to return so we can crash here
		
___main:
			rts

			.bss
		
_basepage:	ds.l	1
_program_length:
			ds.l	1

			.end
