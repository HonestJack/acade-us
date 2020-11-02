#include "Display.h"
#include "Timer.h"
#include "Keyboard.h"
#include "User.h"
#include "Eeprom.h"
#include "Userdatabase.h"
#include "utils.h"
#include "Admin.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

Display display;
Timer timer; 
Keyboard keyboard;
Userdatabase userdatabase(&display, &timer, &keyboard);
Admin admin(&display, &timer, &keyboard, &userdatabase);
Eeprom eeprom;

void showTimeCapacity()
{
  // These lines are executed only on the first call to this function.
  static volatile long counter = START_TIME;
  static volatile long old_counter = counter;

  counter = timer.getTime();
  if (counter != old_counter)
  {
    old_counter = counter;
    display.print_interfacie_padrao(counter, userdatabase.capacity());
  } 
}

void inputHandler(short &key_value)
{
  if(keyboard.getIndex() == DIGIT_NUMBER)
  {
    if(key_value == 12345)
    {
      admin.start();
      keyboard.resetIndex();
      key_value = 0;
    }
    else
    {
      userdatabase.login(key_value);  
      keyboard.resetIndex();
      key_value = 0;

      delay_ms(1000);

      display.print_interfacie_padrao(timer.getTime(), userdatabase.capacity());
      display.limpa_linha(2);
    }
  }
}

int main()
{
  sei();

/*
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
  //while(1);
  */

  short key_value = 0;

  display.print_interfacie_padrao(START_TIME, userdatabase.capacity());

  while(1) 
  {
    showTimeCapacity();

    key_value += keyboard.reading(display);
    
    inputHandler(key_value);
  }
  return 0;
}