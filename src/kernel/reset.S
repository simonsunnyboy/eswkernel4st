 |
 | Entertainment Software Kernel for Atari ST
 | (c) 2016/18/26 by Matthias Arndt / ASM Software
 |
 | The MIT License applies to this software. Refer to the file COPYING for
 | details.
 |
 | @file  reset.S
 | @brief provides routine to perform the reset of the ST
 | @details The implementation assumes that the supervisor mode is already active.
 |
 |

	.global _ESWK_int_ResetST

	.text

_ESWK_int_ResetST:		move.l	4.w,-(sp)    | pull start vector from TOS ROM and place onto stack
			            rts                  | restart TOS
	.end

