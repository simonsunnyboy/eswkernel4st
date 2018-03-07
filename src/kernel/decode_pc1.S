|
| Entertainment Software Kernel for Atari ST
| (c) 2016/18 by Matthias Arndt / ASM Software
|
| The MIT License applies to this software. Refer to the file COPYING for
| details.
|
| @file  decode_pc1.S
| @brief depacking routine for packed DEGAS pictures in RAM
|

.globl _ESWK_DepackPC1Picture
.text

_ESWK_DepackPC1Picture:
	link a6,#0
	movem.l D0-A2,-(SP)

	| initialize registers with values from stack
	move.l 8(a6),a1    | source address
	move.l 12(a6),a0   | destination address
	move.w 16(a6),d0   | number of bytes to depack

	| init depack
	clr d3
	move #200,d6
degas_line:
	move #4,d5
	sub #1,d6
	tst d6
	beq degas_done

degas_color:
	move #40,d4
degas_loop:
	cmp.l #1,d0
	blt degas_done

	sub.l #1,d0
	clr.l d1
	move.b (a1)+,d1
	cmp.b #128,d1
	beq degas_loop

	tst.b d1
	bmi degas_duplicate

degas_copylp:
	move.b (a1)+,(a0)
	sub.l #1,d0
	sub #1,d4

	tst d3
	bne degas_copylp2
	add #1,a0
	move #1,d3
	jmp degas_copyrcrs
degas_copylp2:
	add #7,a0
	clr d3

degas_copyrcrs:
	dbf d1,degas_copylp
	tst d4
	bne degas_loop
	sub #158,a0
	sub #1,d5
	tst d5
	bne degas_color
	add #152,a0
	jmp degas_line

degas_duplicate:
	muls #-1,d1
	and #0xff,d1
	move.b (a1)+,d2
	sub.l #1,d0

degas_duplp:
	move.b d2,(a0)

	sub #1,d4

	tst d3
	bne degas_duplp2
	add #1,a0
	move #1,d3
	jmp degas_duprcrs

degas_duplp2:
	add #7,a0
	clr d3

degas_duprcrs:
	dbf d1,degas_duplp

	tst d4
	bne degas_loop
	sub #158,a0
	sub #1,d5
	tst d5
	bne degas_color
	add #152,a0
	jmp degas_line

degas_done:

	movem.l (SP)+,D0-A2
	unlk a6
	rts
.end
