
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

void Display::clear()
{
  limpa_linha(2);
  limpa_linha(1);
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

void Display::print_tempo_restante(long tempo_restante)
{
  limpa_linha(2);
  goto_display(2,1);
  if (tempo_restante > 0)
  {
    print("Restam: ");
    print_horario(tempo_restante);
  }else{
    print("Seu Tempo Acabou");
  }  
}

void Display::print_relogio(long count)
{
  goto_display(1,1);
  print_horario(count);
}

void Display::print_usuarios_presentes(short capacity)
{
  goto_display(1, 14);
  print("U:");
  print((capacity) + ASCII_SHIFT);
}

void Display::print_interfacie_padrao(long count, short capacity)
{
  limpa_linha(1);
  print_relogio(count);
  print_usuarios_presentes(capacity);
}

void Display::print_duas_linhas(char string1[MAX_STRING_SIZE], char string2[MAX_STRING_SIZE])
{
  limpa_linha(1);
  print(string1);
  limpa_linha(2);
  print(string2);
}

void Display::print_user(short user)
{
  int i;
  short aux;
  for(i=0;i<DIGIT_NUMBER;i++)
  {
    aux = user/pot(10, DIGIT_NUMBER - i - 1);
    print(aux + ASCII_SHIFT);
    user = user - aux*pot(10, DIGIT_NUMBER - i - 1);
  }
}