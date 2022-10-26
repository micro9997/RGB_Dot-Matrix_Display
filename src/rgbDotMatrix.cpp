
#include "rgbDotMatrix.hpp"

using namespace mohan;

RGBDotMatrix::RGBDotMatrix(volatile uint8_t &port, uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) {
    this->port = &port;
    this->dataPin = dataPin;
    this->clockPin = clockPin;
    this->latchPin = latchPin;

    init();
    
    shiftCount = 0;
}

RGBDotMatrix::~RGBDotMatrix() {
    
}

void RGBDotMatrix::init() {
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

    accessDisplay(0, 0, 0, 0);
}

void RGBDotMatrix::accessDisplay(uint8_t comm, uint8_t red, uint8_t green, uint8_t blue) {
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
        shiftOut(data >> (8 * i));
    }

    *port |= (1 << latchPin);
    *port &= ~(1 << latchPin);
}

void RGBDotMatrix::bitsCpy(uint32_t *data, uint8_t dat, uint8_t dir, uint8_t n) {
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

void RGBDotMatrix::shiftOut(uint8_t data) {
    for(int i = 0; i < 8; i++) {
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

void RGBDotMatrix::setData(uint8_t *data, uint8_t dataSize, uint8_t dataLen) {
    ptrData = data;
    this->dataSize = dataSize;
    this->dataLen = dataLen;
}

void RGBDotMatrix::display() {
    for(int i = 0; i < 8; i++) {
        uint8_t mask = (1 << i);
        uint8_t da = (*(ptrData + ((dataSize * i) + (shiftCount / 8))));
        da = da << (shiftCount % 8);
        da = da | ((*(ptrData + ((dataSize * i) + ((shiftCount / 8) + 1)))) >> (8 - (shiftCount % 8)));
        accessDisplay(mask, 0, 0, da);
    }
}

void RGBDotMatrix::move() {
    shiftCount++;
    if(shiftCount == ((dataLen - 8) + 1)) {
        shiftCount = 0;
    }
}
