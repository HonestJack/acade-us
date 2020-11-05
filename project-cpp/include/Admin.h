#ifndef ADMIN_H
#define ADMIN_H

#include "Timer.h"
#include "Display.h"
#include "Keyboard.h"
#include "Userdatabase.h"

#define SENHA_ADMIN 12345

class Admin
{
public:
  Admin(Display *d, Timer *t, Keyboard *k, Userdatabase *u);
  ~Admin();

  void start();

private:
  void entrar_senha_admin(Display display, Keyboard keyboard);

  char readOptionDigit(char num_options);
  void showOptions();

  void menu_report();
  void verifica_usuario_presentes(short login);

  void menu_troca_conta();
  void seleciona_troca(short i);

  void changeTime();
  void changeHour();
  void changeMinute();
  void changeSeconds();
  unsigned short readNewTime();

  Display *display;
	Timer *timer;
	Keyboard *keyboard;  
  Userdatabase *userdatabase;
};


#endif