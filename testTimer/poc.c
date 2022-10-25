
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
	DDRB |= (1 << PORTB5);
	
    // Set CTC Bit
	TCCR0A = (1 << WGM01);
	OCR0A = 250;
	TIMSK0 = (1 << OCIE0A);
	
	sei();
	
    // Start at 64 prescalar
	TCCR0B = (1 << CS01) | (1 << CS00);
	
    while(1) {
        // TODO:: Please write your application code 
    }
}

ISR(TIMER0_COMPA_vect) {
	static int extraTime = 0;
    extraTime++;
	
	if(extraTime > 100) {
		extraTime = 0;
		PORTB ^= (1 << PORTB5);
	}
}
