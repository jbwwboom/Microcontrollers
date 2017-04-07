/*
 * Track6.asm
 *
 *  Created: 7-4-2017 14:25:55
 *   Author: justi
 */ 
start:
	LDI R18, 88
	LDI xh, $02
	MOV xl, R12
	ST X, R18
	


klaar:
	rjmp klaar
