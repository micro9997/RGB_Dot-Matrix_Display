
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

#include "data.h"

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
    rgbDotMatrix.setData(&data[0][0], dataSize, dataLen);
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
