/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait(int);
volatile char currentVal = 0x00;
void SegmentWrite(int);
void PlezierSchrijver(void);

typedef struct {
		int Byte;
		int delay;
}karakters, plezierPatroon;

 karakters table[] = {
	 {0x3F,500}, //0
	 {0x12,500}, //1
	 {0x4F,500}, //2
	 {0x5B,500}, //3
	 {0x72,500}, //4
	 {0xF9,500}, //5
	 {0xFD,500}, //6
	 {0x13,500}, //7
	 {0x7F,500}, //8
	 {0x7B,500}, //9

	 {0x77,500}, //a
	 {0x7C,500}, //b
	 {0x2D,500}, //c
	 {0x5E,500}, //d
	 {0x6F,500}, //e
	 {0x65,500}, //f
	 {0x6D,500}  //E
 };

 plezierPatroon tabel[]  = {
 {0x01,500},
 {0x02,500},
 {0x04,500},
 {0x08,500},
 {0x10,500},
 {0x20,500},
 {0x40,500},
 {0x80,500}
 };



/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
ISR( INT0_vect ) 
/* 
short:			ISR INT0
inputs:			
outputs:	
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
    if(currentVal == 0x00){				//check if you haven't reached 00000000
	    currentVal = 0x80;
	    PORTA = currentVal;
	    }else {
	    currentVal = currentVal >> 1;	// bitshift to next LED
	    PORTA = currentVal;		
		}
}

/******************************************************************/
ISR( INT1_vect )
/* 
short:			ISR INT1
inputs:			
outputs:	
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
    //PORTD &= ~(1<<5);
	
		
			// var to check your current position

			if(currentVal == 0x00){				//check if you haven't reached 00000000
				currentVal = 0x01;
				PORTA = currentVal;
				}else{
				currentVal = currentVal << 1;	// bitshift to next LED
				PORTA = currentVal;
				}
			
				
}

 void SegmentWrite(int write)
 {
	 PORTB = write>16 ? table[16].Byte : table[write].Byte;
 }

 void PlezierSchrijver()
 {
	int i;
	int n = sizeof(tabel)/sizeof(tabel[0]);
	for(i = 0; i < n;i++)
	{
		PORTB = tabel[i].Byte;
		wait(500);
	}
 }


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input
	DDRA = 0xFF;
	PORTA = 0x01;			// set the first bit
	DDRB = 0xFF;

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	//sei();	
		

		
		
	
	

	while (1)
	{
	//int i;
		//for(i = 0; i<17; i++)
		//{
			//SegmentWrite(i);
		//}
		PlezierSchrijver();
					wait(1);
		
		
	}

	return 1;
}