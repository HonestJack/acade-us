#ifndef USER_H
#define USER_H

#include "Display.h"
#include "Keyboard.h"

class User
{
public:
    short login;
    short senha;
    unsigned long tempo_restante;
    char plano;
    bool esta_dentro;

    User(/* args */);
    ~User();
    void entrou(Display display, Keyboard keyboard);
    void saiu();

private:
    void entrar_senha(Display display, Keyboard keyboard);
};

#endif