/*/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "asf.h"
#include "SegmentDisplay.h"
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>





char row[5]        = {0x00,0x00,0x00,0x00};
char player[5]    = {0x80,0x00,0x00,0x00};

int score = 0;
int lost = 0;


void update(void);
void wait(int);
void init_timer(void);

int main (void)
{
	TotalInit();
	clearDisplay();

    // Init LCD
    //init_4bits_mode();


    board_init();
    
    

    DDRD = 0xFF;            // open all ports
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRG = 0x00;

    
    init_timer();

    int re1 = 0, re2 = 0;

    while(1)
    {
		CalculateScore(score);
		writeCustomDisplay();
      if(!(PING & (1 << PG4)))
     {
        if(re1 == 0) {
            re1 = 1;
            char dummy;
            dummy = player[0];
            player[0] = player[1];
            player[1]=player[2];
            player[2]=player[3];
            player[3]=dummy;
            wait(200);
        }
      }else {
        re1 = 0;
     }

     if(!(PING & (1 << PG2)))
     {
        if(re2 == 0) {
            re2 = 1;
            char dummy;
            dummy = player[3];
            player[3] = player[2];
            player[2]=player[1];
            player[1]=player[0];
            player[0]=dummy;
            wait(200);
        }
     } else {
        re2 = 0;
     }
     wait(1);
    }

    

    /* Insert application code here, after the board has been initialized. */
}





void update (void){
    
        //display
        int rnd = rand() % 5;
        if(rnd > 0)
        {
        
            //row[rand() % 4] |= 0x01;
			row[rand() % 4] |= 0x08;
        }
    
	
    
    score++;
    int i;
    for(i=0;i<5;i++){
		row[i] &= 0b11111000;
        row[i] = row[i] << 1;

        if((row[i] & player[i])){
            lost=1;
        }else{
            row[i] |= player[i];
        }

    }


    PORTA = (row[0] |= 0b00000111);
    PORTB = (row[1] |= 0b00000111);
    PORTC = (row[2] |= 0b00000111);
    PORTD = (row[3] |= 0b00000111);
    /*
    for(i=0; i<5;i++){
        if(row[i] | player[i]){
            
        }
    }

        int i;
        char gameOver = 0x80;
        for(i=0;i<=4;i++){

            if(player[i] == 0x80){
                for(i=0;i<=4;i++){
                    if(row[i] >= 0x80){
                        lost = 1;
                    }
                }
            }
        }*/

    //lcd_write_string("score: " + score);
}


ISR ( TIMER1_OVF_vect )
{
    TCNT1 = 100; // Herlaad de timer
    if(!lost)
    {
    update();
    }
}

void init_timer(){
    DDRE |= (1 << 0);

    TIMSK |= (1 << TOIE1 ); 
    sei () ; 
    
    TCNT1 = 100; 
    TCCR1B |= ((1 << CS10 ) | (1 << CS11 )) ;
    }