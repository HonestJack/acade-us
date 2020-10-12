#include "utils.h"

#include <avr/io.h>

void timer_us(unsigned short tempo){
	unsigned short presc;
	TCCR0A = 2;        // Timer modo CTC
	
	if (tempo <= 128)
	{
		TCCR0B = 2;        // Prescaler 8
		presc = 8;
	}else if(tempo <= 1024)
	{
		TCCR0B = 3;        // Prescaler 64
		presc = 64;
	}else
	{
		TCCR0B = 4;        // Prescaler 256
		presc = 256;
	}
	
	TCNT0  = 0;                    // Zera o timer
	OCR0A =	tempo/(0.0625*presc);  // 1000u/(0.625u*presc)
	TIFR0 |= (1 << 0);             // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}