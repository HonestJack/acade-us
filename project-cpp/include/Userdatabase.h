#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "User.h"

#define QUANTIDADE_DE_USUARIOS 11
#define MAXIMO_USUARIOS_PRESENTES 5

class Userdatabase
{
public:
	Userdatabase(Display *d, Timer *t, Keyboard *k, Eeprom *e);
	~Userdatabase();
	
	short capacity();
	void login(short valor_digitado);

	User usuarios[QUANTIDADE_DE_USUARIOS];

private:
	
	void entra_ou_sai(unsigned char i);
  
	short m_capacity;

	Display *display;
	Timer *timer;
	Keyboard *keyboard;
	Eeprom *eeprom;

};



#endif