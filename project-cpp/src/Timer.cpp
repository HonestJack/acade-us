#include "Timer.h"

#include <avr/interrupt.h>

volatile unsigned long Timer::counter = 0;

ISR (TIMER1_OVF_vect) // Interrup��o do timer respons�vel por contar os segundos
{
	TCNT1  = 3036;
	TIFR1 |= (1 << 0); // Clear Flag
	Timer::counter++;
}

Timer::Timer(/* args */)
{
  TCCR1A = 0;        // Timer
	TCCR1B = 4;        // Prescaler 256
	TCNT1  = 3036;
//	OCR1A  = 62500;        //  1 000 000u/(0.0625u*presc)
	TIFR1 |= (1 << 0); // Clear Flag
	TIMSK1 = (1 << 0); // Ativa interrupt do Timer1
}

Timer::~Timer()
{
}

volatile unsigned long Timer::getTime()
{
  return counter;
}