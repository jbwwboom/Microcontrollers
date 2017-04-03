; Replace with your application code
start:
	ldi R16, 0
	ldi R17, 7
    out PORTA, R16

lus: 
    inc R16
	out PORTA, R16
	dec R17
	brne lus

lamp:
	ldi R17, 7

lus1: 
    dec R16
	out PORTA, R16
	dec R17
	brne lus1

klaar:
	rjmp start
