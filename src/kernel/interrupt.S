 |
 | Entertainment Software Kernel for Atari ST
 | (c) 2016/18 by Matthias Arndt / ASM Software
 |
 | The MIT License applies to this software. Refer to the file COPYING for
 | details.
 |
 | @file  interrupt.S
 | @brief installs and provides interrupt services routines
 | @details Timer C is installed to provide both a 50 hz and 200 hz hook to the user.
 |
 |

	.global _ESWK_int_InitInterrupts

	.text

	.equ timer_c_vector, 0x114  | vector address of timer C
	.equ vblqueue, 0x456        | address of vblqueue system variable

| *** initialize interrupts ***
_ESWK_int_InitInterrupts:
	clr.w tccount
	move.l	timer_c_vector,oldtc		                | store old timer c to jump to it
	move.l	#_ESWK_TimerC_ISR,timer_c_vector 		    | new timer c vector
	| traverse vblqueue
	move.l vblqueue,a0                          | pointer to VBL queue
loop_vbl_queue:
	move.l (a0)+,a1
	cmp.l   #0,a1
	bne     loop_vbl_queue
	move.l  #_UserCode_VBL_ISR, -(a0)           | store user VBL routine into VBL queue
    rts


| *** new Timer C ISR for calling user routines ***
_ESWK_TimerC_ISR:
	movem.l	a0-a6/d0-d7,-(sp)
	jsr _UserCode_200Hz_ISR     | call user 200hz routine
	addq.w #1,tccount
	cmpi.w #4,tccount
	blt no50hzcall              | check if this is the 4th call...
	clr.w tccount               | reset counter if yes
	jsr _UserCode_50Hz_ISR      | call user 50hz routine for the 4th call of the ISR

no50hzcall:
	movem.l	(sp)+,a0-a6/d0-d7
	move.l	oldtc,-(sp) 	    | system friendly jump to old Timer C
	rts
|............................................................................

	.bss
tccount:	dc.w	0    | count number of interrupts to issue user call every 4th call
oldtc:		ds.l	1
	.end

