#ifndef ADMIN_H
#define ADMIN_H

#include "Timer.h"
#include "Display.h"
#include "Keyboard.h"

class Admin
{
public:
  Admin(Display *d, Timer *t, Keyboard *k);
  ~Admin();

  void start();

private:
  char readOptionDigit(char num_options);
  void showOptions();

  void changeTime();
  void changeHour();
  void changeMinute();
  void changeSeconds();
  unsigned short readNewTime();

  Display *display;
	Timer *timer;
	Keyboard *keyboard;  
};


#endif