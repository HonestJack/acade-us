#include "Display.h"
#include "Timer.h"
#include "Keyboard.h"
#include "utils.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

volatile unsigned int old_counter = 0;
volatile unsigned int counter = 0;

/*
void init()
{
  DDRB   = 0xFF;   // PB como saida
  sei();
}
*/

int main()
{
//  init(); // ALWAYS THE FIRST LINE
  sei();

  Display display;
  Timer timer; 
  Keyboard keyboard;

  unsigned char key;

  unsigned char vec_value[DIGIT_NUMBER];
  unsigned char vec_index = 0;
  unsigned char user_test[DIGIT_NUMBER] = {6, 6, 6, 6, 6};
  unsigned char key_counter = 0;

  display.print_hora(0);

  while(1) 
  {

    counter = timer.getTime();
    if (counter != old_counter)
    {
      old_counter = counter;
      display.print_hora(counter);
    } 

    key = keyboard.reading();
    if(key)
    {
      display.goto_display(2, vec_index+1);
      if(vec_index == 0)
      {
        display.print("                ");
        display.goto_display(2, vec_index+1);
      }
      display.print(key);
      vec_value[vec_index] = key - ASCII_SHIFT;
      vec_index++;
    }

    if(vec_index == DIGIT_NUMBER)
    {
      for(vec_index = 0; vec_index < DIGIT_NUMBER; vec_index++)
      {
        if (vec_value[vec_index] == user_test[vec_index])
        {
          key_counter++;
        } 
      }
      display.goto_display(2, 1);
      if (key_counter == DIGIT_NUMBER)
      {
        display.print("Bem-Vindo");
      }else
      {
        display.print("User n existe");
      }  
      vec_index = 0;
    }

  }
  return 0;
}