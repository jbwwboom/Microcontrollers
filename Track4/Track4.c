/*
 * Track4.c
 *
 * Created: 15-3-2017 09:51:33
 *  Author: justi
 */

 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdbool.h>
 #include <math.h>
 #include <stdlib.h>

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

	void spi_masterInit(void)
	{
		DDR_SPI = 0xff; // All pins output: MOSI, SCK, SS, SS_display
		DDR_SPI &= ~BIT(SPI_MISO); // except: MISO input
		PORT_SPI |= BIT(SPI_SS); // SS_ADC == 1: deselect slave
		SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1); // or: SPCR = 0b11010010;
		// Enable spi, MasterMode, Clock rate fck/64
		// bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
	}

	// Write a byte from master to slave
	void spi_write( unsigned char data )
	{
		SPDR = data; // Load byte --> starts transmission
		while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
	}

	// Write a byte from master to slave and read a byte from slave - not used here
	char spi_writeRead( unsigned char data )
	{
		SPDR = data; // Load byte --> starts transmission
		while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
		data = SPDR; // New received data (eventually, MISO) in SPDR
		return data; // Return received byte
	}

	// Select device on pinnumer PORTB
	void spi_slaveSelect(unsigned char chipNumber)
	{
		PORTB &= ~BIT(chipNumber);
	}

	// Deselect device on pinnumer PORTB
	void spi_slaveDeSelect(unsigned char chipNumber)
	{
		PORTB |= BIT(chipNumber);
	}

	void displayInit()
	{
		spi_slaveSelect(0); // Select display chip (MAX7219)
		spi_write(0x09); // Register 09: Decode Mode
		spi_write(0xFF); // -> 1's = BCD mode for all digits
		spi_slaveDeSelect(0); // Deselect display chip
		spi_slaveSelect(0); // Select dispaly chip
		spi_write(0x0A); // Register 0A: Intensity
		spi_write(0x0F); // -> Level 4 (in range [1..F])
		spi_slaveDeSelect(0); // Deselect display chip
		spi_slaveSelect(0); // Select display chip
		spi_write(0x0B); // Register 0B: Scan-limit
		spi_write(0x03); // -> 1 = Display digits 0..1
		spi_slaveDeSelect(0); // Deselect display chip
		spi_slaveSelect(0); // Select display chip
		spi_write(0x0C); // Register 0B: Shutdown register
		spi_write(0x01); // -> 1 = Normal operation
		spi_slaveDeSelect(0); // Deselect display chip
	}

 }
