
gcc generateData.c -o generateData.out
./generateData.out

avr-g++ -mmcu=atmega328p main.cpp src/rgbDotMatrix.cpp -o main.out
avr-objcopy -O ihex main.out out.hex

echo "Please upload the hex file to the MCU manually"
echo " "

rm generateData.out main.out
