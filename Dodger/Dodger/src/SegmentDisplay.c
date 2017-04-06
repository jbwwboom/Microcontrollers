/*
 * Track4c.c
 *
 * Created: 6-4-2017 14:14:55
 *  Author: justi
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>
#include "asf.h"
#include <stdlib.h>
#include <stdio.h>
#define BIT(x) ( 1<<x )
#define DDR_SPI DDRB // spi Data direction register
#define PORT_SPI PORTB // spi Output register
#define SPI_SCK 1 // PB1: spi Pin System Clock
#define SPI_MOSI 2 // PB2: spi Pin MOSI
#define SPI_MISO 3 // PB3: spi Pin MISO
#define SPI_SS 0 // PB0: spi Pin Slave Select
#include "SegmentDisplay.h"


static int *scoreArray;

void InitScoreArray(void){
	scoreArray = (int) malloc(sizeof(int) * 4);
	int i;
	for(i = 0; i < 4; i++){
		scoreArray = 0;
	}
}

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	_delay_ms(1);
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


void displayDriverInit(void)
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


void displayOn(void)
{
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x01); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}


void displayOff(void)
{
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x00); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}

void clearDisplay(void){
	// write 4-digit data
	for (char i =1; i<=4; i++)
	{
		spi_slaveSelect(0); // Select display chip
		spi_write(i); // digit adress: (digit place)
		spi_write(0); // digit value: 0
		spi_slaveDeSelect(0); // Deselect display chip
		wait(100);
	}
}

void spi_writeWord(unsigned char address, unsigned char data){
	spi_slaveSelect(0); // Select display chip
	spi_write(address); // digit adress
	spi_write(data); // digit value
	spi_slaveDeSelect(0); // Deselect display chip
}

void writeDisplay(void){
	// clear display (all zero's)
	for (char i =1; i<=4; i++)
	{
	spi_slaveSelect(0); // Select display chip
	spi_write(i); // digit adress: (digit place)
	spi_write(5-i); // digit value: i (= digit place)
	spi_slaveDeSelect(0); // Deselect display chip
	}
}

void CalculateScore(int score){
	if(score / 10 <  1){
		scoreArray[0] = 0;
		scoreArray[1] = 0;
		scoreArray[2] = 0;
		scoreArray[3] = score;
		}else if(score / 100 < 1){
		scoreArray[0] = 0;
		scoreArray[1] = 0;
		scoreArray[2] = score / 10;
		scoreArray[3] = score % 10;
		}else if(score / 1000 < 1){
		scoreArray[0] = 0;
		scoreArray[1] = score / 100;
		scoreArray[2] = (score % 100) % 100 / 10;
		scoreArray[3] = (score % 100) % 10;
		}else{
		scoreArray[0] = score / 1000;
		scoreArray[1] = (score % 1000) / 100;
		scoreArray[2] = (score % 100) % 100 / 10;
		scoreArray[3] = (score % 100) % 10;
		}
}



void writeCustomDisplay(){
	for (char i =1; i<=4; i++)
	{
		spi_slaveSelect(0); // Select display chip
		spi_write(i); // digit adress: (digit place)
		spi_write(scoreArray[5 - (i+1)]); // digit value: i (= digit place)
		spi_slaveDeSelect(0); // Deselect display chip

	}
	}	


void TotalInit(void){
	DDRB =0x01; // Set PB0 pin as output for display select
	spi_masterInit(); // Initialize spi module
	displayDriverInit(); // Initialize display chip	
	wait(1000);
}