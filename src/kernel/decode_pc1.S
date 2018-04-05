|
| Entertainment Software Kernel for Atari ST
| (c) 2016/18 by Matthias Arndt / ASM Software
|
| The MIT License applies to this software. Refer to the file COPYING for
| details.
|
| @file   decode_pc1.S
| @brief  depacking routine for packed DEGAS pictures in RAM with file header and palette information
| @author rockyone (used from atari-forum.com post on Mon Mar 19, 2018 2:28 am)
|

.globl _ESWK_DepackPC1Picture
.text

_ESWK_DepackPC1Picture:
	movem.l d0-d7/a0-a6,-(sp)
	movem.l	64(sp),a0-a1    | working pointers from stack

	cmp.b #0x80,(a0)
	bne file_not_packed

	move.b	1(a0),d1	    | Image resolution

	| copy header data, mark as unpacked DEGAS file and copy palette to destination
	clr.b (a1)
	move.b 1(a0),1(a1)
	move.w 2(a0),2(a1)
	move.w 4(a0),4(a1)
	move.w 6(a0),6(a1)
	move.w 8(a0),8(a1)
	move.w 10(a0),10(a1)
	move.w 12(a0),12(a1)
	move.w 14(a0),14(a1)
	move.w 16(a0),16(a1)
	move.w 18(a0),18(a1)
	move.w 20(a0),20(a1)
	move.w 22(a0),22(a1)
	move.w 24(a0),24(a1)
	move.w 26(a0),26(a1)
	move.w 28(a0),28(a1)
	move.w 30(a0),30(a1)
	move.w 32(a0),32(a1)

	| skip header at source and destination for unpacking
	lea.l	34(a0),a0
	lea.l	34(a1),a1

	lea.l	32000(a1),a5	| End of the destination

depackt:
	moveq.l	#3,d2
	lsr.b	d1,d2		    | Number of plans -1
	move.b	d2,d3
	lsl.b	#1,d3
	moveq.l	#1,d4 		    | Offset for next byte

All_lines:
	movea.l	a1,a3 	        | First plane of a line
	move.w	d2,d1		    | Reset the number of plans
	lea.l	160(a3),a6	    | End of a line

plans_line:
	movea.l	a3,a2

Recup_code:
	moveq.l	#0,d0
	move.b 	(a0)+,d0
	bmi.s 	Repete_code 	| <

Copy_code:
	move.b 	(a0)+,(a2)
	adda.w	d4,a2           | offest for next byte
	eor.b 	d3,d4 		    |   7/1  3/1   1/1
	dbra.w	d0,Copy_code
	bra.s	End_line

Repete_code:
	neg.b 	d0 		        | +
	move.b	(a0)+,d5
Recopy_code:
	move.b 	d5,(a2)
	adda.w 	d4,a2
	eor.b 	d3,d4
	dbra.w 	d0,Recopy_code

End_line:
	cmpa.l	a2,a6           | End of a pane of a line ?
	bhi.s 	Recup_code 	    | >

	addq.l	#2,a3		    | next plan
	dbra.w 	d1,plans_line

	movea.l	a6,a1		    | next line
	cmpa.l	a1,a5
	bhi.s	All_lines

file_not_packed:
	movem.l (sp)+,d0-d7/a0-a6
	rts

.end
