#include "Admin.h"
#include <stdlib.h>

#define TEMPO_B (long)60*60*60
#define TEMPO_P (long)10
#define TEMPO_M 1
#define TEMPO_X 0

Admin::Admin(Display *d, Timer *t, Keyboard *k, Userdatabase *u, Eeprom *e)
{
  display = d;
  timer = t;
  keyboard = k;
  userdatabase = u;
  eeprom = e;
}

Admin::~Admin()
{
}

void Admin::entrar_senha_admin(Display display, Keyboard keyboard)
{
    short key_value = 0;
    char index_old = 0;
    keyboard.resetIndex();
    
    display.limpa_linha(2);
    display.limpa_linha(1);
    display.goto_display(1, 1);
    display.print("Senha:");

    while((key_value != SENHA_ADMIN) || (keyboard.getIndex() < DIGIT_NUMBER))
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
            if(key_value != SENHA_ADMIN){
                display.goto_display(2, 1);
                display.print("Incorreto...");
                key_value = 0;
                keyboard.resetIndex();
                index_old = 0;
            }
        }
    }
}

void Admin::start()
{
  char option;
  entrar_senha_admin(*display, *keyboard);
  do
  {
    showOptions();
    option = readOptionDigit(4);
    switch (option)
    {
      case 1:
        changeTime();
        break;
      case 2:
        menu_troca_conta();
        break;
      case 3:
        menu_report();
        break;
      case 4:
        break;
    }
  }while(option != 4);

  display->clear();
}

char Admin::readOptionDigit(char num_options)
{
  char key = 0;
  char option=0;
  do
  {
    while (key==0)
    {
      key = keyboard->readRow();
      keyboard->nextRow();
    }
    option = key - '0';
    key = 0;
  } while (option < 1 || option > num_options);

  return option;
}

void Admin::showOptions()
{
  // display->clear();
  // display->print_duas_linhas("ADMIN MODE","Feel the POWER!");

  // delay_ms(2500);

  display->clear();
  display->print_duas_linhas("1-Time 2-Account","3-Report 4-Exit");
}

void Admin::changeTime()
{
  char option;

  do
  {
    display->clear();
    display->print_duas_linhas("1-Hour 2-Minutes","3-Seconds 4-Exit");

    option = readOptionDigit(4);
    switch (option)
    {
      case 1:
        changeHour();
        break;
      case 2:
        changeMinute();
        break;
      case 3:
        changeSeconds();
        break;
      case 4:
        break;
    }
  }while(option != 4);

}

void Admin::changeHour()
{  
  display->clear();
  display->print("Update Hour:");
  display->goto_display(2,1);

  short newHour=0;
  do
  {  
    newHour = readNewTime();
  } while (newHour > 24);

  long time = timer->getTime();
  long hours = time/3600;
  long min_sec = time - hours*3600;
  long min = min_sec/60;
  long sec = min_sec-min*60;

  timer->setTime(newHour*(long)3600 + min*(long)60 + sec);
}

void Admin::changeMinute()
{  
  display->clear();
  display->print("Update Minutes:");
  display->goto_display(2,1);

  short newMinute=0;
  do
  {  
    newMinute = readNewTime();
  } while (newMinute > 59);

  long time = timer->getTime();
  long hours = time/(long)3600;
  long min_sec = time - hours*(long)3600;
  long min = min_sec/(long)60;
  long sec = min_sec-min*(long)60;
  
  timer->setTime(hours*(long)3600 + newMinute*(long)60 + sec);

  // display->limpa_linha(1);
  // char str[10];
  // ltoa(min,str,10);
  // display->print(str);
  // display->limpa_linha(2);
  // ltoa(newMinute,str,10);
  // display->print(str);
  // while(1);
}

void Admin::changeSeconds()
{  
  display->clear();
  display->print("Update Seconds:");
  display->goto_display(2,1);

  short newSeconds=0;
  do
  {  
    newSeconds = readNewTime();
  } while (newSeconds > 59);

  long time = timer->getTime();
  long hours = time/3600;
  long min_sec = time - hours*3600;
  long min = min_sec/60;
    
  timer->setTime(hours*(long)3600 + min*(long)60 + newSeconds);
}

unsigned short Admin::readNewTime()
{
  unsigned short key_value = 0;
  keyboard->resetIndex();
  do
  {
    key_value += keyboard->reading(*display);
  } while(keyboard->getIndex() < 2);
  
  // IF we type 12 
  // keyboard->reading(*display) returns 12000
  // to get 12 we divide by 1000

  return key_value/1000;  
}

void Admin::verifica_usuario_presentes(short login)
{
  if (userdatabase->capacity()>0)
  {
    display->print_menu_deslizante(login);
  }else
  {
    display->limpa_linha(2);
    display->print("Nenhum Presente");
  }

}

void Admin::menu_report()
{ 
  char option;
  short i = 0, j;

  short presentes[MAXIMO_USUARIOS_PRESENTES];

  for (j = 0; j < QUANTIDADE_DE_USUARIOS; j++)
  {
    if(userdatabase->usuarios[j].esta_dentro)
    {
      presentes[i] = userdatabase->usuarios[j].login;
      i++;
    }
  }
  i = 0;

  display->limpa_linha(2);
  display->limpa_linha(1);
  display->print("0");
  display->print(userdatabase->capacity() + ASCII_SHIFT);
  display->print(" Pres:  3-Exit");
  
  do
  {
    verifica_usuario_presentes(presentes[i]);
    option = readOptionDigit(3);
    switch (option)
    {
      case 1:
        i++;
        if (i >= userdatabase->capacity())
        {
          i = 0;
        }     
        break;
      case 2:
        i--;
        if (i < 0)
        {
          i = userdatabase->capacity() - 1;
        }  
        break;
      case 3:
        break;
    }
  }while(option != 3);
}


void Admin::menu_troca_conta()
{
  char option;
  short i = 0;

  display->limpa_linha(2);
  display->limpa_linha(1);
  display->print("3-Exit  4-Select");

  do
  {
    display->print_menu_deslizante(userdatabase->usuarios[i].login);
    option = readOptionDigit(4);
    switch (option)
    {
      case 1:
        i++;
        if (i >= QUANTIDADE_DE_USUARIOS)
        {
          i = 0;
        }     
        break;
      case 2:
        i--;
        if (i < 0)
        {
          i = QUANTIDADE_DE_USUARIOS - 1;
        }  
        break;
      case 3:
        break;
      case 4:
        seleciona_troca(i);
        option = 3;
        break;
    }
  }while(option != 3);
  

}

void Admin::seleciona_troca(short i)
{
  char option;
  display->limpa_linha(1);
  display->print_user(userdatabase->usuarios[i].login);
  display->print(": ");
  display->print(userdatabase->usuarios[i].plano);
  display->limpa_linha(2);
  display->print("1-B 2-P 3-M 4-X");
  do
  {
    option = readOptionDigit(9);
    switch (option)
    {
      case 1:
                userdatabase->usuarios[i].tempo_restante = TEMPO_B;
                userdatabase->usuarios[i].plano = 'B';
                break;
      case 2:
                userdatabase->usuarios[i].tempo_restante = TEMPO_P;
                userdatabase->usuarios[i].plano = 'P';
                break;
      case 3:
                userdatabase->usuarios[i].tempo_restante = TEMPO_M;
                userdatabase->usuarios[i].plano = 'M';
                break;
      case 4:
                userdatabase->usuarios[i].tempo_restante = TEMPO_X;
                userdatabase->usuarios[i].plano = 'X';
                break;
      default:
                display->limpa_linha(1);
                display->print("Wrong Plan!");
                break;
    }
  } while (option < 1 || option > 4);
  eeprom->escreve(i,userdatabase->usuarios[i].plano);
  display->limpa_linha(1);
  display->print("Troca confirmada");
  display->limpa_linha(2);
  display->print(eeprom->at(i));
  delay_ms(2000);
}
