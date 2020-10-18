
#include "display.h"

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

void Display::print(char string[MAX_STRING_SIZE])
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

void Display::limpa_linha(unsigned char linha)
{
  goto_display(linha, 1);
  print("                ");
  goto_display(linha, 1);
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

void Display::print_usuarios_presentes(short usuarios_presentes)
{
  goto_display(1, 14);
  print("U:");
  print((usuarios_presentes) + ASCII_SHIFT);
}

void Display::print_interfacie_padrao(unsigned int count, short usuarios_presentes)
{
  print_hora(count);
  print_usuarios_presentes(usuarios_presentes);
}