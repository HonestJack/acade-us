#ifndef USER_H
#define USER_H

#include "Timer.h"
#include "Display.h"
#include "Keyboard.h"
#include "Eeprom.h"

class User
{
public:
    short login;
    short senha;
    long tempo_restante;
    char plano;
    bool esta_dentro;

    User(/* args */);
    ~User();
    void entrou(Display display, Keyboard keyboard, Timer timer);
    void saiu(Display display, Timer timer);

private:
    void entrar_senha(Display display, Keyboard keyboard);
    long tempo_de_entrada;
};

#endif