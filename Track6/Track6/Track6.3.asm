/*
 * Track6.asm
 *
 *  Created: 7-4-2017 14:44:42
 *   Author: justi
 */ 

start:
	LDI R17, 11
	ldi xh, $06 
	ldi	xl, $60
	ldi yh, $08 
	ldi yl, $B0

loop:
	ld R18, X+
	ST Y+, R18
	dec R17
	brne loop


	


klaar:
	rjmp klaar