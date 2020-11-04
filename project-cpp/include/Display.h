#ifndef DISPLAY_H
#define DISPLAY_H

#include "Lcd.h"
#include "utils.h"

#define DISPLAY_DELAY 3


class Display
{
public:
  Display(/* args */);
  ~Display();

  void print(char ch);
  void print(char string[MAX_STRING_SIZE]);
  void goto_display(unsigned char linha, unsigned char coluna);
  void print_interfacie_padrao(long int count, short capacity);
  void clear();
  void limpa_linha(unsigned char linha);
  void print_tempo_restante(long tempo_restante);
  void print_duas_linhas(char string1[MAX_STRING_SIZE], char string2[MAX_STRING_SIZE]);
  void print_horario(long count);
  void print_user(short user);
  void print_menu_deslizante(short user);
private:
 
  void print_relogio(long count);
  void print_usuarios_presentes(short capacity);
  Lcd m_lcd;
};

#endif