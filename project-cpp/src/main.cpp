#include "Display.h"
#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>


#define PORTD_COLUMN_MASK 0x70 // 0b01110000 - Pega apenas as colunas do teclado
#define COLUNA_0 0x60 // 0b0110 0000
#define COLUNA_1 0x50 // 0b0110 0000
#define COLUNA_2 0x30 // 0b0110 0000

#define PORTD_LINES_MASK  0x0F // 0b00001111 - Pega apenas as linhas do teclado
#define LINHA_3 0x07 // 0b00000111
#define LINHA_2 0x0B // 0b00001011
#define LINHA_1 0x0D // 0b00001101
#define LINHA_0 0x0E // 0b00001110

#define BOUNCE 8


volatile unsigned int old_counter = 0;
volatile unsigned int counter = 0;

void init()
{
	DDRB   = 0xFF;   // PB como saida

	DDRD   |=  (1 << 0);   // PD.0 como saida - Linha 0 do teclado
  DDRD   |=  (1 << 1);   // PD.1 como saida - Linha 1 do teclado
  DDRD   |=  (1 << 2);   // PD.2 como saida - Linha 2 do teclado
  DDRD   |=  (1 << 3);   // PD.3 como saida - Linha 3 do teclado

  DDRD   &= ~(1 << 4);   // PD.4 como entrada - Coluna 0 do teclado
  DDRD   &= ~(1 << 5);   // PD.5 como entrada - Coluna 1 do teclado
  DDRD   &= ~(1 << 6);   // PD.6 como entrada - Coluna 2 do teclado

  PORTD |=  (1 << 4); //Ativa pull up
  PORTD |=  (1 << 5); //Ativa pull up
  PORTD |=  (1 << 6); //Ativa pull up

  DDRD   |=  (1 << 7);   // PD.7 como saida - R/S do display

  sei();
}


void timer_1ms(){
 unsigned short presc;
	TCCR0A = 2;        // Timer modo CTC
	TCCR0B = 3;        // Prescaler 8
	presc = 64;
	TCNT0  = 0;                    // Zera o timer
	OCR0A =	1000/(0.0625*presc);  // 1000u/(0.625u*presc)
	TIFR0 |= (1 << 0);             // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}

// Função que faz o deboucing
void deboucing(unsigned char b_antigo){
	unsigned char count = 0, b_novo = 0x00;
	do{
		timer_1ms();
		b_novo = PORTD & PORTD_COLUMN_MASK;
		if(b_novo == b_antigo){
			count++;
		}else{
			count = 0;
		}
		b_antigo = b_novo;
	}while(count < BOUNCE);
}

unsigned char le_teclado(Display display, unsigned char PD_antigo[4], unsigned char linha, unsigned char i)
{
  PORTD &= 0xF0;
  PORTD |= linha; // 0bxxxx1101
  if(PD_antigo[i] != (PIND & PORTD_COLUMN_MASK))
  {
    deboucing(PIND & PORTD_COLUMN_MASK);
    switch (PIND & PORTD_COLUMN_MASK){
      case COLUNA_0: // P0 = 0b0110 0000 = 0xB0
        switch (linha)
        {
          case LINHA_0:
            display.m_lcd.print('1');
            break;
          case LINHA_1:
            display.m_lcd.print('4');
            break;
          case LINHA_2:
            display.m_lcd.print('7');
            break;
          case LINHA_3:
            display.m_lcd.print('*');
          default:
            break;
        }
        break;

      case COLUNA_1: // P0 = 0b0101 0000 = 0xD0
        switch (linha)
        {
          case LINHA_0:
            display.m_lcd.print('2');
            break;
          case LINHA_1:
            display.m_lcd.print('5');
            break;
          case LINHA_2:
            display.m_lcd.print('8');
            break;
          case LINHA_3:
            display.m_lcd.print('0');
            break;
          default:
            break;
        }
        break;
      case COLUNA_2: // P0 = 0b0011 0000 = 0xE0
        switch (linha)
        {
          case LINHA_0:
            display.m_lcd.print('3');
            break;
          case LINHA_1:
            display.m_lcd.print('6');
            break;
          case LINHA_2:
            display.m_lcd.print('9');
            break;
          case LINHA_3:
            display.m_lcd.print('#');
          break;
          default:
            break;
        }
        break;
      default:
        break;
    }
    return(PIND & PORTD_COLUMN_MASK);
  }
  return(PD_antigo[i]);
}

unsigned char proxima_linha(unsigned char linha_atual)
{
  switch (linha_atual)
  {
  case LINHA_0:
    return LINHA_1;
    break;
  case LINHA_1:
    return LINHA_2;
    break;
  case LINHA_2:
    return LINHA_3;
    break;
  case LINHA_3:
    return LINHA_0;
    break;
  default:
    return LINHA_0;
    break;
  }

}

int main()
{
  init(); // ALWAYS THE FIRST LINE

  Display display;
  Timer timer; 

  unsigned char i = 0;
  unsigned char PD_antigo[4];
  unsigned char linha = LINHA_0;
  PD_antigo[0] = PIND & PORTD_COLUMN_MASK;
  linha = LINHA_1;
  PD_antigo[1] = PIND & PORTD_COLUMN_MASK;
  linha = LINHA_2;
  PD_antigo[2] = PIND & PORTD_COLUMN_MASK;
  linha = LINHA_3;
  PD_antigo[3] = PIND & PORTD_COLUMN_MASK;
  

  display.print_hora(0);

  while(1) 
  {
    counter = timer.getTime();
    if (counter != old_counter)
    {
      old_counter = counter;
    // display.print_hora(counter);
    }
    
    PD_antigo[i] = le_teclado(display, PD_antigo, linha, i);
    linha = proxima_linha(linha);
    i++;
    if(i == 4) i = 0;

  }
  return 0;
}