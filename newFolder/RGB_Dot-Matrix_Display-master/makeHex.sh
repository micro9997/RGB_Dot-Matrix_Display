
avr-g++ -mmcu=atmega328p main.cpp src/shiftReg.cpp
avr-objcopy -O ihex a.out out.hex

rm a.out
