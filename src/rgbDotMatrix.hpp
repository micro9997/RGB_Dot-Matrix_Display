
#ifndef RGBDOTMATRIX_HPP
#define RGBDOTMATRIX_HPP

#define F_CPU 16000000

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>

#define LSBFIRST 0
#define MSBFIRST 1

namespace mohan {
    class RGBDotMatrix {
    private:
        volatile uint8_t *port;
        uint8_t dataPin;
        uint8_t clockPin;
        uint8_t latchPin;
        uint8_t *ptrData;
        uint8_t dataSize;
        uint8_t dataLen;
        uint8_t shiftCount;
        void init();
        void accessDisplay(uint8_t, uint8_t, uint8_t, uint8_t);
        void bitsCpy(uint32_t *, uint8_t, uint8_t, uint8_t);
        void shiftOut(uint8_t);
    public:
        RGBDotMatrix(volatile uint8_t &, uint8_t, uint8_t, uint8_t);
        ~RGBDotMatrix();
        void setData(uint8_t *, uint8_t, uint8_t);
        void display();
        void move();
    };
}

#endif
