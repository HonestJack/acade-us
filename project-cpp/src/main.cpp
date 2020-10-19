#include "Display.h"
#include "Timer.h"
#include "Keyboard.h"
#include "User.h"
#include "Eeprom.h"
#include "Userdatabase.h"
#include "utils.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>


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
  Userdatabase userdatabase;
  Eeprom eeprom;

  eeprom.append('C');
  display.print(eeprom.at(0));
  eeprom.append('A');
  display.print(eeprom.at(1));
  eeprom.append('R');
  display.print(eeprom.at(2));
  eeprom.append('L');
  display.print(eeprom.at(3));
  eeprom.append('I');
  display.print(eeprom.at(4));
  eeprom.append('T');
  display.print(eeprom.at(5));
  eeprom.append('O');
  display.print(eeprom.at(6));
  while(1);

  volatile unsigned long old_counter = 0;
  volatile unsigned long counter = 0;

  short key_value = 0;

  display.print_interfacie_padrao(counter, userdatabase.usuarios_presentes);

  while(1) 
  {

    counter = timer.getTime();
    if (counter != old_counter)
    {
      old_counter = counter;
      display.print_interfacie_padrao(counter, userdatabase.usuarios_presentes);
    } 

    key_value += keyboard.reading(display);
    
    if(keyboard.value_index == DIGIT_NUMBER)
    {
      userdatabase.login(display, keyboard, key_value);  
      keyboard.value_index = 0;
      key_value = 0;
    }

  }
  return 0;
}