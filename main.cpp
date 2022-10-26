
#define F_CPU 16000000

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "src/rgbDotMatrix.hpp"

#define dataPin     7
#define clockPin    6
#define latchPin    5

using namespace mohan;

uint8_t testData[8][3] = {  {0x00, 0x00, 0x00},
                            {0x00, 0x88, 0x00},
                            {0x00, 0x88, 0x00},
                            {0x00, 0x50, 0x00},
                            {0x00, 0x20, 0x00},
                            {0x00, 0x50, 0x00},
                            {0x00, 0x88, 0x00},
                            {0x00, 0x88, 0x00}};

uint8_t data[8][8] = {  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                        {0x00, 0xFA, 0x2F, 0xBC, 0xFA, 0x2F, 0x80, 0x00},
                        {0x00, 0x83, 0x68, 0x22, 0x22, 0x28, 0x00, 0x00},
                        {0x00, 0x82, 0xA8, 0x22, 0x21, 0x48, 0x00, 0x00},
                        {0x00, 0xF2, 0x2F, 0x3C, 0x20, 0x8F, 0x00, 0x00},
                        {0x00, 0x82, 0x28, 0x28, 0x21, 0x48, 0x00, 0x00},
                        {0x00, 0x82, 0x28, 0x24, 0x22, 0x28, 0x00, 0x00},
                        {0x00, 0xFA, 0x2F, 0xA2, 0x22, 0x2F, 0x80, 0x00}};
uint8_t dataSize = 3;
uint8_t dataLen = 21;
uint8_t moveTime = 250;

RGBDotMatrix rgbDotMatrix(PORTD, dataPin, clockPin, latchPin);

void timerInit() {
    DDRB |= (1 << PORTB5);
	TCCR0A = (1 << WGM01);
	OCR0A = 250;
	TIMSK0 = (1 << OCIE0A);
	sei();
	TCCR0B = (1 << CS01) | (1 << CS00);
}

int main(void) {
    timerInit();
    rgbDotMatrix.setData(&testData[0][0], dataSize, dataLen);
    while(1) {
        rgbDotMatrix.display();
    }

    return 0;
}

ISR(TIMER0_COMPA_vect) {
	static int extraTime = 0;
    extraTime++;
	
	if(extraTime > moveTime) {
		extraTime = 0;
		rgbDotMatrix.move();
	}
}
