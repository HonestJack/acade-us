#ifndef DISPLAY_H
#define DISPLAY_H

#include "Lcd.h"

class Display
{
public:
  Display(/* args */);
  ~Display();

  void print(char ch);
  void print_hora(unsigned int count);

private:
  Lcd m_lcd;
};

#endif