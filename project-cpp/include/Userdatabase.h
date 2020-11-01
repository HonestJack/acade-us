#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "User.h"


#define QUANTIDADE_DE_USUARIOS 11

class Userdatabase
{
public:
	Userdatabase(Display *d, Timer *t, Keyboard *k);
	~Userdatabase();
	
	short capacity();
	void login(short valor_digitado);

private:
	User usuarios[QUANTIDADE_DE_USUARIOS];
	void entra_ou_sai(unsigned char i);
  
	short m_capacity;

	Display *display;
	Timer *timer;
	Keyboard *keyboard;

};



#endif