#include "Admin.h"

#include <stdlib.h>

Admin::Admin(Display *d, Timer *t, Keyboard *k)
{
  display = d;
  timer = t;
  keyboard = k;
}

Admin::~Admin()
{
}

void Admin::start()
{
  char option;

  do
  {
    showOptions();
    option = readOptionDigit(4);
    switch (option)
    {
      case 1:
        changeTime();
        break;
      case 2:
        /* code */
        break;
      case 3:
        /* code */
        break;
      case 4:
        break;
    }
  }while(option != 4);

  display->clear();
}

char Admin::readOptionDigit(char num_options)
{
  char key = 0;
  char option=0;
  do
  {
    while (key==0)
    {
      key = keyboard->readRow();
      keyboard->nextRow();
    }
    option = key - '0';
  } while (option < 1 || option > num_options);

  return option;
}

void Admin::showOptions()
{
  // display->clear();
  // display->print_duas_linhas("ADMIN MODE","Feel the POWER!");

  // delay_ms(2500);

  display->clear();
  display->print_duas_linhas("1-Time 2-Account","3-Report 4-Exit");
}

void Admin::changeTime()
{
  char option;

  do
  {
    display->clear();
    display->print_duas_linhas("1-Hour 2-Minutes","3-Seconds 4-Exit");

    option = readOptionDigit(4);
    switch (option)
    {
      case 1:
        changeHour();
        break;
      case 2:
        changeMinute();
        break;
      case 3:
        changeSeconds();
        break;
      case 4:
        break;
    }
  }while(option != 4);

}

void Admin::changeHour()
{  
  display->clear();
  display->print("Update Hour:");
  display->goto_display(2,1);

  short newHour=0;
  do
  {  
    newHour = readNewTime();
  } while (newHour > 24);

  long time = timer->getTime();
  long hours = time/3600;
  long min_sec = time - hours*3600;
  long min = min_sec/60;
  long sec = min_sec-min*60;

  timer->setTime(newHour*(long)3600 + min*(long)60 + sec);
}

void Admin::changeMinute()
{  
  display->clear();
  display->print("Update Minutes:");
  display->goto_display(2,1);

  short newMinute=0;
  do
  {  
    newMinute = readNewTime();
  } while (newMinute > 59);

  long time = timer->getTime();
  long hours = time/(long)3600;
  long min_sec = time - hours*(long)3600;
  long min = min_sec/(long)60;
  long sec = min_sec-min*(long)60;
  
  timer->setTime(hours*(long)3600 + newMinute*(long)60 + sec);

  // display->limpa_linha(1);
  // char str[10];
  // ltoa(min,str,10);
  // display->print(str);
  // display->limpa_linha(2);
  // ltoa(newMinute,str,10);
  // display->print(str);
  // while(1);
}

void Admin::changeSeconds()
{  
  display->clear();
  display->print("Update Seconds:");
  display->goto_display(2,1);

  short newSeconds=0;
  do
  {  
    newSeconds = readNewTime();
  } while (newSeconds > 59);

  long time = timer->getTime();
  long hours = time/3600;
  long min_sec = time - hours*3600;
  long min = min_sec/60;
    
  timer->setTime(hours*(long)3600 + min*(long)60 + newSeconds);
}

unsigned short Admin::readNewTime()
{
  unsigned short key_value = 0;
  keyboard->resetIndex();
  do
  {
    key_value += keyboard->reading(*display);
  } while(keyboard->getIndex() < 2);
  
  // IF we type 12 
  // keyboard->reading(*display) returns 12000
  // to get 12 we divide by 1000

  return key_value/1000;  
}