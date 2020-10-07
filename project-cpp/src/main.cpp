#include "Display.h"
#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

volatile unsigned int old_counter = 0;
volatile unsigned int counter = 0;

void init()
{
	DDRB   = 0xFF;   // PB como sa�da
	DDRD   = 0xFF;   // PD como sa�da
  sei();
}

int main()
{
  init(); // ALWAYS THE FIRST LINE

  Display display;
  Timer timer; 

  display.print_hora(0);

  while(1) 
  {
    counter = timer.getTime();
    if (counter != old_counter)
    {
      old_counter = counter;
      display.print_hora(counter);
    }
  }

  return 0;
}