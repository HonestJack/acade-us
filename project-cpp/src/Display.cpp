#include "Display.h"

Display::Display(/* args */)
{
}

Display::~Display()
{
}

void Display::print(char ch)
{
  m_lcd.print(ch);
}



void Display::print_hora(unsigned int count)
{
  int aux_1, aux_2;
 
  aux_1 = count/3600;
  aux_2 = aux_1/10;

  m_lcd.print(aux_2 + 48);
  m_lcd.print(aux_1 - 10*aux_2 + 48);
  m_lcd.print(':');

  count = count - 3600*aux_1;
  aux_1 = count/60;
  aux_2 = aux_1/10;

  m_lcd.print(aux_2 + 48);
  m_lcd.print(aux_1 - 10*aux_2 + 48);
  m_lcd.print(':');

  aux_1 = count - 60*aux_1;
  aux_2 = aux_1/10;

  m_lcd.print(aux_2 + 48);
  m_lcd.print(aux_1 - 10*aux_2 + 48);
}