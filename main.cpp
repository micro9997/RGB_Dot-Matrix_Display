
#define F_CPU 16000000

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include "src/rgbDotMatrix.hpp"

#define dataPin     7
#define clockPin    6
#define latchPin    5

using namespace mohan;

int main(void) {
    uint8_t data[8][8] = {  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                            {0x00, 0xFA, 0x2F, 0xBC, 0xFA, 0x2F, 0x80, 0x00},
                            {0x00, 0x83, 0x68, 0x22, 0x22, 0x28, 0x00, 0x00},
                            {0x00, 0x82, 0xA8, 0x22, 0x21, 0x48, 0x00, 0x00},
                            {0x00, 0xF2, 0x2F, 0x3C, 0x20, 0x8F, 0x00, 0x00},
                            {0x00, 0x82, 0x28, 0x28, 0x21, 0x48, 0x00, 0x00},
                            {0x00, 0x82, 0x28, 0x24, 0x22, 0x28, 0x00, 0x00},
                            {0x00, 0xFA, 0x2F, 0xA2, 0x22, 0x2F, 0x80, 0x00}};

    uint8_t dataLen = 57;
    
    RGBDotMatrix rgbDotMatrix(PORTD, dataPin, clockPin, latchPin);

    uint8_t wait = 25;
    uint8_t add = 0;

    while(1) {
        for(int i = 0; i < 8; i++) {
            uint8_t mask = (1 << i);

            uint8_t da = data[i][(add / 8)];
            da = da << (add % 8);
            da = da | (data[i][(add / 8) + 1] >> (8 - (add % 8)));

            rgbDotMatrix.accessDisplay(mask, 0, 0, da);
        }
        wait--;
        if(wait == 0) {
            add++;
            if(add == ((dataLen - 8) + 1)) {
                add = 0;
            }
            wait = 25;
        }
    }

    return 0;
}

// add == 50

// rgbDotMatrix.accessDisplay(mask, 0, 0, ((data2[i] >> 6) >> ((57 - 8) - add)));

/* uint8_t data[8][8] = {  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                            {0x00, 0x7D, 0x17, 0xDE, 0x7D, 0x17, 0xC0, 0x00},
                            {0x00, 0x41, 0xB4, 0x11, 0x11, 0x14, 0x00, 0x00},
                            {0x00, 0x41, 0x54, 0x11, 0x10, 0xA4, 0x00, 0x00},
                            {0x00, 0x79, 0x57, 0x9E, 0x10, 0x47, 0x80, 0x00},
                            {0x00, 0x41, 0x14, 0x14, 0x10, 0xA4, 0x00, 0x00},
                            {0x00, 0x41, 0x14, 0x12, 0x11, 0x14, 0x00, 0x00},
                            {0x00, 0x7D, 0x17, 0xD1, 0x11, 0x17, 0xC0, 0x00}}; */

/* while(1) {
    for(int i = 0; i < 8; i++) {
        uint8_t mask = (1 << i);

        uint8_t da = data[i][((add - 1) / 8)];
        da = da << (add % 8);
        da = da | (data[i][((add - 1) / 8) + 1] >> (8 - (add % 8)));

        rgbDotMatrix.accessDisplay(mask, 0, 0, da);
    }
    wait--;
    if(wait == 0) {
        add++;
        if(add == (dataLen + 1)) {
            add = 0;
        }
        wait = 25;
    }
} */

/* while(1) {
    for(int i = 0; i < 8; i++) {
        uint8_t mask = (1 << i);

        uint8_t da = data[i][0];
        da = da << 8;
        da = da | (data[i][1] >> 0);

        rgbDotMatrix.accessDisplay(mask, 0, 0, da);
    }
    wait--;
    if(wait == 0) {
        add++;
        if(add == (dataLen + 1)) {
            add = 0;
        }
        wait = 25;
    }
} */

/* while(1) {
    for(int i = 0; i < 8; i++) {
        uint8_t mask = (1 << i);

        uint8_t da = data[i][((add - 1) / 8)];
        da = da << (add % 9);
        da = da | (data[i][((add - 1) / 8) + 1] >> (8 - (add % 9)));

        rgbDotMatrix.accessDisplay(mask, 0, 0, da);
    }
    wait--;
    if(wait == 0) {
        add++;
        if(add == ((dataLen - 8) + 1)) {
            add = 0;
        }
        wait = 25;
    }
} */

/* uint64_t data2[] = {0x0000000000000000, 0x007D17DE7D17C000, 0x0041B41111140000, 0x0041541110A40000,
                        0x0079579E10478000, 0x0041141410A40000, 0x0041141211140000, 0x007D17D11117C000}; */
