
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

void Display::print_horario(long count)
{
  long aux_1, aux_2;

  aux_1 = count/3600;
  aux_2 = aux_1/10;

  m_lcd.print(aux_2 + ASCII_SHIFT);
  m_lcd.print(aux_1 - 10*aux_2 + ASCII_SHIFT);
  m_lcd.print(':');

  count = count - 3600*aux_1;
  aux_1 = count/60;
  aux_2 = aux_1/10;

  m_lcd.print(aux_2 + ASCII_SHIFT);
  m_lcd.print(aux_1 - 10*aux_2 + ASCII_SHIFT);
  m_lcd.print(':');

  aux_1 = count - 60*aux_1;
  aux_2 = aux_1/10;

  m_lcd.print(aux_2 + ASCII_SHIFT);
  m_lcd.print(aux_1 - 10*aux_2 + ASCII_SHIFT);
}

void Display::print_tempo_restante(long count)
{
  limpa_linha(2);
  goto_display(2,1);
  if (count > 0)
  {
    print("Restam: ");
    print_horario(count);
  }else{
    print("Seu Tempo Acabou");
  }
  
  
}

void Display::print_relogio(long count)
{
  goto_display(1,1);
  print_horario(count);
}

void Display::print_usuarios_presentes(short usuarios_presentes)
{
  goto_display(1, 14);
  print("U:");
  print((usuarios_presentes) + ASCII_SHIFT);
}

void Display::print_interfacie_padrao(long count, short usuarios_presentes)
{
  limpa_linha(1);
  print_relogio(count);
  print_usuarios_presentes(usuarios_presentes);
}