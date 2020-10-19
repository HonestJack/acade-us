#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "User.h"


#define QUANTIDADE_DE_USUARIOS 11

#define MAXIMO_USUARIOS_PRESENTES 5

#define TEMPO_B (long)60*60*60
#define TEMPO_P (long)10
#define TEMPO_M 1
#define TEMPO_X 0

static short lista_clientes [11] =
{
	18040,
	28869,
	23105,
	12941,
	26264,
	28870,
	26265,
	26272,	 
	24393,
	24391,
	28868
};
	
static short lista_senhas [11] =
{
	18040,
	28869,
	23105,
	12941,
	26264,
	28870,
	26265,
	26272,	 
	24393,
	24391,
	28868
};
	
static char lista_planos [11] =
{
	'M', 
	'P',
	'B', 
	'P', 
	'X', 
	'M', 
	'P', 
	'M', 
	'B', 
    'X', 
    'P'
};

class Userdatabase
{
private:
	User usuarios[QUANTIDADE_DE_USUARIOS];
	void entra_ou_sai(Display display, Keyboard keyboard, Timer timer, unsigned char i);
    
public:
    Userdatabase(/* args */);
    ~Userdatabase();
	short usuarios_presentes;
    void login(Display display, Keyboard keyboard, Timer timer, short valor_digitado);
};



#endif