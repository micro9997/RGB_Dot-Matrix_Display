
avr-g++ -mmcu=atmega328p poc.c
avr-objcopy -O ihex a.out out.hex

rm a.out
