/*
 * Track4.c
 *
 * Created: 15-3-2017 09:51:33
 *  Author: justi
 */

 #include "lcd.h";

 void Delay( int ms )
 {
	 for (int i=0; i<ms; i++)
	 {
		 _delay_ms( 1 );
	 }
 }

 void Track4B1(){
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;

	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;

	while(1){
		PORTA = ADCH;
		PORTB = ADCL;
	}
 }

 void Track4B2(){
	DDRF = 0x00;
	DDRA - 0xFF;

	ADMUX = 0b11100001;
	ADCSRA = 0b1000110;

	while(1){
		ADCSRA |= 1 << (6);
		while(ADCSRA & 1 << (6)){
			PORTA = ADCH;
			Delay(500);
		}
	}	
 }

 void Track4B3(){
	DDRF = 0x00;
	DDRA = 0xFF;

	ADMUX = 0b11100001;
	ADCSRA = 0b11100110;

	initlcd();
	Delay(300);
	char displayTemp[15];
	clearScreen();

	while(1){
		clearScreen():
		int i = ADCH;
		sprintf(displayTemp, "%i°C");
		Delay(5);

		display_text(displayTemp);
		Delay(5);
		memset(displayTemp, 0,15);
		PORTA = ADCH;
		Delay(2000);
	}

 }
