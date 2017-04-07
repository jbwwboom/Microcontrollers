;
; Track6.2.asm
;
; Created: 7-4-2017 14:12:12
; Author : justi
;


start:
	ldi R16, 11
	ldi xh, $0a //Tussen 0a60H en 0a70H
	ldi xl, $60
	ldi yh, $0a
	ldi yl, $70

lus: 
    ld R17, X+
	ST Y+, R17
	com R16
	brne lus



klaar:
	rjmp klaar