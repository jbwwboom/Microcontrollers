/*
 * Week1.c
 *
 * Created: 23-2-2017 10:12:58
 *  Author: justi
 */ 

void b2(void){
		DDRD = 0b11111111;

		PORTD = 0b0100000;

		while(1){
			PORTD ^= 0b11000000;
			_delay_ms(500);
		}
}

void b3(void){
		DDRD = 0xFF;
		DDRC = 0x00;
		while(1){
				if(PINC & 1){
					PORTD ^= 0b10000000;
					_delay_ms(50);
				}
		}
}

void b4(void){
		DDRD = 0xFF;
		PORTD = 0x01;
		char currentPos = 0x01;

		while(1){
				if(currentPos == 0x00){
					currentPos = 0x01;
					PORTD = currentPos;
				}else{
					currentPos = currentPos << 1;
					PORTD = currentPos;
				}
				_delay_ms(50)
		}
}


//Hier kun je je eigen pattern invoegen door extra array waarde toe te voegen.

unsigned char test[] = {{0x84}, {0x82}, {NULL}};

void b5(void){
	DDRD = 0xff;
	int i = 0;
	while(1){
		while((test[i]) != NULL){
			PORTD = test[i];
			_delay_ms(50);
			i++;
		}			
	}
}

void b6(void){
		DDRD = 0xFF;
		DDRC = 0x00;
		PORTD = 0x80;
		int delay = 1000;
		while(1){
			if(PINC & 1){
				if(delay == 1000){
				//8 keer zo snel
					delay = 125;
				}else{
					delay = 1000;
				}
			}
			PORTD ^= 0x80;
			_delay_ms(delay)
		}
}

