#include "Userdatabase.h"


Userdatabase::Userdatabase(/* args */)
{
    unsigned char i;
    usuarios_presentes = 0;
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

void Userdatabase::entra_ou_sai(Display display, Keyboard keyboard, Timer timer, unsigned char i)
{
    if(usuarios[i].esta_dentro)
    {
        usuarios[i].saiu(display, timer);
        usuarios_presentes--;
    }else
    {   
        if((usuarios_presentes < MAXIMO_USUARIOS_PRESENTES) && (usuarios[i].tempo_restante > 0))
        {
            usuarios[i].entrou(display, keyboard, timer);
            usuarios_presentes++;
        }else
        {
            if(usuarios[i].tempo_restante <= 0)
            {
                display.print_duas_linhas("Voce Nao Possui", "Tempo Disponivel");
            }else
            {
                display.print_duas_linhas("Ocup limitada", "Pelo Covid");
            }
        }
    }
}

void Userdatabase::login(Display display, Keyboard keyboard, Timer timer,  short valor_digitado)
{
    bool usuario_existente = false;
    unsigned char i;
    display.goto_display(2, 1);
    for (i = 0; i < QUANTIDADE_DE_USUARIOS; i++)
    {   
        if (valor_digitado == usuarios[i].login)
        {
            usuario_existente = true;
            entra_ou_sai(display, keyboard, timer, i);
        }        
    }
    if(!usuario_existente)
    {
        display.print_duas_linhas("Usuario Digitado", "Nao Existe");
    }
}
