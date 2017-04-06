/*
 * SegmentDisplay.h
 *
 * Created: 6-4-2017 14:32:29
 *  Author: justi
 */ 


#ifndef SEGMENTDISPLAY_H_
#define SEGMENTDISPLAY_H_

void InitScoreArray(void);
void wait(int);
void spi_masterInit(void);
void spi_write( unsigned char );
char spi_writeRead( unsigned char);
void spi_slaveSelect(unsigned char);
void spi_slaveDeSelect(unsigned char);
void displayDriverInit(void);
void displayOn(void);
void displayOff(void);
void clearDisplay(void);
void writeDisplay(void);
void CalculateScore(int);
void spi_writeWord(unsigned char, unsigned char);
void writeCustomDisplay();
void TotalInit(void);




#endif /* SEGMENTDISPLAY_H_ */