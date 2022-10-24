
#ifndef SHIFTREG_HPP
#define SHIFTREG_HPP

#define F_CPU 16000000

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>

#define LSBFIRST 0
#define MSBFIRST 1

namespace mohan {
    class ShiftReg {
    private:
        volatile uint8_t *port;
        uint8_t dataPin;
        uint8_t clockPin;
        uint8_t latchPin;
        void init();
    public:
        ShiftReg(volatile uint8_t &, uint8_t, uint8_t, uint8_t);
        ~ShiftReg();
        uint8_t shiftOut(uint8_t, uint8_t);
    };
}

#endif
