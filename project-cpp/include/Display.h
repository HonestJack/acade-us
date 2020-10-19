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
  void print_interfacie_padrao(long int count, short usuarios_presentes);
  void limpa_linha(unsigned char linha);
  void print_tempo_restante(long count);

private:
  void print_horario(long count);
  void print_relogio(long count);
  void print_usuarios_presentes(short usuarios_presentes);
  Lcd m_lcd;
};

#endif