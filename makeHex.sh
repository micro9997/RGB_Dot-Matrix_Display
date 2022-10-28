
gcc generateData.c -o generateData.out
./generateData.out

avr-g++ -mmcu=atmega328p main.cpp src/rgbDotMatrix.cpp -o main.out
avr-objcopy -O ihex main.out out.hex

rm generateData.out main.out
