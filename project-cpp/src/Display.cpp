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

void Display::print(char string[])
{
  m_lcd.print(string);
}

void Display::goto_display(unsigned char linha, unsigned char coluna)
{
  if(linha == 2)
  {
    coluna |= 0x40;
  }
  m_lcd.lcd_function(0x80 | (coluna - 1));
}

void Display::print_hora(unsigned int count)
{
  int aux_1, aux_2;
  
  goto_display(1,1);

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