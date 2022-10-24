
avr-g++ -mmcu=atmega328p main.cpp src/rgbDotMatrix.cpp
avr-objcopy -O ihex a.out out.hex

rm a.out
