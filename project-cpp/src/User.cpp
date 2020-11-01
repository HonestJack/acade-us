#include "User.h"

User::User(/* args */)
{
}

User::~User()
{
}

void User::entrar_senha(Display display, Keyboard keyboard)
{
    short key_value = 0;
    char index_old = 0;
    keyboard.resetIndex();
    
    display.limpa_linha(2);
    display.limpa_linha(1);
    display.goto_display(1, 1);
    display.print("Senha:");

    while((key_value != senha) || (keyboard.getIndex() < DIGIT_NUMBER))
    {
        key_value += keyboard.reading(display);

        if(index_old != keyboard.getIndex())
        {
            index_old = keyboard.getIndex();;
            display.goto_display(2, keyboard.getIndex());
            display.print('*');
        }

        if(keyboard.getIndex() == DIGIT_NUMBER)
        {
            if(key_value != senha){
                display.goto_display(2, 1);
                display.print("Incorreto...");
                key_value = 0;
                keyboard.resetIndex();
                index_old = 0;
            }
        }
    }
}

void User::entrou(Display display, Keyboard keyboard, Timer timer)
{
    entrar_senha(display, keyboard);
    esta_dentro = 1;
    tempo_de_entrada = timer.getTime();
    display.limpa_linha(1);
    display.print("Bem-vindo");

    if(plano != 'M')
    {
        display.print_tempo_restante(tempo_restante);
    }else
    {
        display.limpa_linha(2);
        display.print("Aproveite");
    }
    
    
}

void User::saiu(Display display, Timer timer)
{
    esta_dentro = 0;
    
    display.limpa_linha(1);
    display.print("Volte logo");
    if (plano != 'M')
    {
        tempo_restante -= timer.getTime() - tempo_de_entrada;
        display.print_tempo_restante(tempo_restante);
    }
    
}