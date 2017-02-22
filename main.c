

#include <avr/io.h>
#include <util/delay.h>


 void init(void)
 {
	 lcd_command( 0x02 );
	 lcd_command( 0x28 );
	 lcd_command( 0x0C );
	 lcd_command( 0x06 );
	 lcd_command( 0x80 );
 }

 void set_cursor(int position){
	 lcd_command( 0x02 );
	 lcd_command( 0x0F );
	 if(position<32){
	 if (position<16)
	 {
		 for (int i = 0; i < position; i++)
		 {
			 lcd_command( 0x14 );
			 _delay_ms(1);
		 }
		 } else {
		 lcd_command( 0xC0 );
		 _delay_ms(1);
		 for (int i = 0; i < position-16; i++)
		 {
			 lcd_command( 0x14 );
			 _delay_ms(1);
		 }
	 }
	 }
 }

 void lcd_command ( unsigned char dat )
 {
	 PORTC = dat & 0xF0;
	 PORTC = PORTC | 0x08;
	 _delay_ms(1);
	 PORTC = 0x04;
	 PORTC = (dat & 0x0F) << 4;
	 PORTC = PORTC | 0x08;
	 _delay_ms(1);
	 PORTC = 0x00;
 }

 void lcd_writeChar( unsigned char dat )
 {
	 PORTC = dat & 0xF0;
	 PORTC = PORTC | 0x0C;
	 _delay_ms(1);
	 PORTC = 0x04;
	 PORTC = (dat & 0x0F) << 4;
	 PORTC = PORTC | 0x0C;
	 _delay_ms(1);
	 PORTC = 0x00;
 }

 void display_text ( char text1[] )
 {
	 lcd_command(0x80);
	 for (int i=0; i<16; i++) {
		 lcd_writeChar( text1[i] );
	 }
 }

 void display_text2 ( char text2[] )
 {
	 lcd_command(0xC0);
	 for (int i=0; i<16; i++) {
		 lcd_writeChar( text2[i] );
	 }
 }

 void lcd_shift(int direction){
	 _delay_ms(10);
	 if(direction == 0){
		 lcd_command(0x1C);
		 }else if(direction == 1){
		 lcd_command(0x18);
	 }
	 _delay_ms(10);
 }

 int count = 0;

 ISR ( TIMER1_OVF_vect )
 {
	 TCNT1 = 100000;
	 count += 1;
	 if(count >= 10){
		count = 0;
	 }
 }

 ISR ( TIMER2_OVF_vect ){
	TCNT2 = 100000;
	lcd_command(0x80);
	_delay_ms(15);
	lcd_command(0x00);
	_delay_ms(25);
 }


 void init_timer()
 {
	 
	 sei ();
	 
	 TCNT1 = 100000;
	 TCNT2 = 100000;
 }



int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
		while(1){
				char write = '0' count;
				lcd_writeChar(write);
				_delay_ms(1);
		}
}
