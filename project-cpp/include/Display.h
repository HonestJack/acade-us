#ifndef DISPLAY_H
#define DISPLAY_H

#include "Lcd.h"

class Display
{
public:
  Display(/* args */);
  ~Display();

  void print(char ch);
  void print(char string[]);
  void print_hora(unsigned int count);
  void goto_display(unsigned char linha, unsigned char coluna);

private:
  Lcd m_lcd;
};

#endif