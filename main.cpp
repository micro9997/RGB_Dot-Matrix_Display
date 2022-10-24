
#define F_CPU 16000000

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "src/rgbDotMatrix.hpp"

#define dataPin     7
#define clockPin    6
#define latchPin    5

using namespace mohan;

ShiftReg firstSR(PORTD, dataPin, clockPin, latchPin);

void bitsCpy(uint32_t *data, uint8_t dat, uint8_t dir, uint8_t n) {
    if(dir == LSBFIRST) {
        for(int i = 0; i < n; i++) {
            uint8_t mask = 1;
            if((dat & (mask << i)) != 0) {
                *data = *data << 1;
                *data = *data | 1;
            } else {
                *data = *data << 1;
                *data = *data & ~1;
            }
        }
    } else if(dir == MSBFIRST) {
        for(int i = 0; i < n; i++) {
            uint8_t mask = 1 << 7;
            if((dat & (mask >> i)) != 0) {
                *data = *data << 1;
                *data = *data | 1;
            } else {
                *data = *data << 1;
                *data = *data & ~1;
            }
        }
    }
}

void accessDisplay(uint8_t comm, uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t data;

    red = ~red;
    green = ~green;
    blue = ~blue;

    bitsCpy(&data, comm, MSBFIRST, 4);  
    bitsCpy(&data, green, MSBFIRST, 8);
    bitsCpy(&data, (comm << 4), MSBFIRST, 4);
    bitsCpy(&data, red, LSBFIRST, 8);
    bitsCpy(&data, blue, LSBFIRST, 8);

    for(int i = 0; i < 4; i++) {
        firstSR.shiftOut(LSBFIRST, (data >> (8 * i)));
    }

    PORTD |= (1 << latchPin);
    PORTD &= ~(1 << latchPin);
}

int main(void) {
    uint8_t data[] = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};

    while(1) {
        for(int i = 0; i < 8; i++) {
            uint8_t mask = (1 << i);
            accessDisplay(mask, data[i], 0, 0);
            // _delay_ms(25);
        }
    }

    // accessDisplay(0b11111111, 0b10011011, 0b01010111, 0b00101111);
    
    return 0;
}
