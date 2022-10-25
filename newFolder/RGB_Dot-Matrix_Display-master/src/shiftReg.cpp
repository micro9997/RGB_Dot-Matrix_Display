
#include "shiftReg.hpp"

using namespace mohan;

ShiftReg::ShiftReg(volatile uint8_t &port, uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) {
    this->port = &port;
    this->dataPin = dataPin;
    this->clockPin = clockPin;
    this->latchPin = latchPin;

    init();
}

ShiftReg::~ShiftReg() {
    
}

void ShiftReg::init() {
    *port &= ~(1 << dataPin);
    *port &= ~(1 << clockPin);
    *port &= ~(1 << latchPin);

    if(port == &PORTB) {
        DDRB |= (1 << dataPin);
        DDRB |= (1 << clockPin);
        DDRB |= (1 << latchPin);
    } else if(port == &PORTC) {
        DDRC |= (1 << dataPin);
        DDRC |= (1 << clockPin);
        DDRC |= (1 << latchPin);
    } else if(port == &PORTD) {
        DDRD |= (1 << dataPin);
        DDRD |= (1 << clockPin);
        DDRD |= (1 << latchPin);
    }

    shiftOut(LSBFIRST, 0b00000000);
}

uint8_t ShiftReg::shiftOut(uint8_t dir, uint32_t data) {
    if(dir == LSBFIRST) {
        for(int i = 0; i < 32; i++) {
            uint32_t mask = (1 << i);
            if((data & mask) != 0) {
                *port |= (1 << dataPin);
            } else {
                *port &= ~(1 << dataPin);
            }
            *port |= (1 << clockPin);
            *port &= ~(1 << clockPin);
            // _delay_ms(25);
        }
    } else if(dir == MSBFIRST) {
        for(int i = 7; i >= 0; i--) {
            uint8_t mask = (1 << i);
            if((data & mask) != 0) {
                *port |= (1 << dataPin);
            } else {
                *port &= ~(1 << dataPin);
            }
            *port |= (1 << clockPin);
            *port &= ~(1 << clockPin);
        }
    }
    
    *port |= (1 << latchPin);
    *port &= ~(1 << latchPin);

    return 0;
}
