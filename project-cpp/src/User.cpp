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
    keyboard.value_index = 0;
    
    display.limpa_linha(2);
    display.limpa_linha(1);
    display.goto_display(1, 1);
    display.print("Senha:");

    while((key_value != senha) || (keyboard.value_index < DIGIT_NUMBER))
    {
        key_value += keyboard.reading(display);

        if(index_old != keyboard.value_index)
        {
            index_old = keyboard.value_index;
            display.goto_display(2, keyboard.value_index);
            display.print('*');
        }

        if(keyboard.value_index == DIGIT_NUMBER)
        {
            if(key_value != senha){
                display.goto_display(2, 1);
                display.print("Incorreto...");
                key_value = 0;
                keyboard.value_index = 0;
                index_old = 0;
            }
        }
    }
}

void User::entrou(Display display, Keyboard keyboard)
{
    entrar_senha(display, keyboard);
    esta_dentro = 1;
}

void User::saiu()
{
    esta_dentro = 0;
}