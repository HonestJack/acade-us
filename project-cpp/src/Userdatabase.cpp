#include "Userdatabase.h"

#include <stdlib.h>


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


Userdatabase::Userdatabase(Display *d, Timer *t, Keyboard *k)
{
    display = d;
    timer = t;
    keyboard = k;

    unsigned char i;
    m_capacity = 0;
    for(i=0; i<QUANTIDADE_DE_USUARIOS; i++)
    {
        usuarios[i].login = lista_clientes[i];
        usuarios[i].senha = lista_senhas[i];
        usuarios[i].plano = lista_planos[i];
        usuarios[i].esta_dentro = 0;
        switch (usuarios[i].plano)
        {
            case 'B':
                usuarios[i].tempo_restante = TEMPO_B;
                break;
            case 'P':
                usuarios[i].tempo_restante = TEMPO_P;
                break;
            case 'M':
                usuarios[i].tempo_restante = TEMPO_M;
                break;
            case 'X':
                usuarios[i].tempo_restante = TEMPO_X;
                break;
            default:
                break;
        }
    }
}

Userdatabase::~Userdatabase()
{
}

void Userdatabase::entra_ou_sai(unsigned char i)
{
    if(usuarios[i].esta_dentro)
    {
        usuarios[i].saiu(*display, *timer);
        m_capacity--;
    }else
    {   
        if((m_capacity < MAXIMO_USUARIOS_PRESENTES) && (usuarios[i].tempo_restante > 0)  && timer->is_open())
        {
            usuarios[i].entrou(*display, *keyboard, *timer);
            m_capacity++;
        }else
        {
            if(!timer->is_open())
            {
                display->print_duas_linhas("Academia", "Fechada");
            }else if(usuarios[i].tempo_restante <= 0)
            {
                display->print_duas_linhas("Voce Nao Possui", "Tempo Disponivel");
            }else
            {
                display->print_duas_linhas("Ocup limitada", "Pelo Covid");
            }
        }
    }
}

short Userdatabase::capacity()
{
    return m_capacity;
}

void Userdatabase::login(short valor_digitado)
{
    bool usuario_existente = false;

    // char t_String1[10];
    // char t_String2[10];
    // display->limpa_linha(2);
    // display->limpa_linha(1);

    for (unsigned char i = 0; i < QUANTIDADE_DE_USUARIOS; i++)
    {   
        // itoa(usuarios[i].login, t_String1, 10);
        // itoa(valor_digitado, t_String2, 10);

        // display->limpa_linha(1);     
        // display->print("U: ");   
        // display->print(t_String1);
        // display->limpa_linha(2);
        // display->print("K: ");     
        // display->print(t_String2);

        // delay_ms(1000);
        if (valor_digitado == usuarios[i].login)
        {
            usuario_existente = true;
            entra_ou_sai(i);
        }        
    }
    if(!usuario_existente)
    {
        display->print_duas_linhas("Usuario Digitado", "Nao Existe");
    }
}
