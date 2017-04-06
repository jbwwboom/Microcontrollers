start:
	ldi R17, $55
	STS $540, R17 //STS is store direct to data space 
	//ofterwijl dit geeft de gekozen geheugengeplaatsen de gekeuze waarde 
	STS $541, R17
	STS $542, R17
	STS $543, R17
	STS $544, R17
	STS $545, R17
	STS $546, R17
	STS $547, R17
	STS $548, R17

klaar:
	rjmp klaar