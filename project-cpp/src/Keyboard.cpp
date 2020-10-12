#include "Keyboard.h"
#include "Display.h"

#include "utils.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define PORTD_COLUMN_MASK 0x70 // 0b0111 0000 - Pega apenas as colunas do teclado

#define COLUNA_0 0x60 // 0b0110 0000
#define COLUNA_1 0x50 // 0b0101 0000
#define COLUNA_2 0x30 // 0b0011 0000

#define COLUNA_0_MASK 0x10 // 0b0001 0000
#define COLUNA_1_MASK 0x20 // 0b0010 0000
#define COLUNA_2_MASK 0x40 // 0b0100 0000

#define PORTD_LINES_MASK  0x0F // 0b00001111 - Pega apenas as linhas do teclado
#define LINHA_3 0x07 // 0b00000111
#define LINHA_2 0x0B // 0b00001011
#define LINHA_1 0x0D // 0b00001101
#define LINHA_0 0x0E // 0b00001110

#define BOUNCE 4

Keyboard::Keyboard(/* args */)
{
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

  // Init row control variables
  m_rowMaskNow = LINHA_0;
  m_rowCount = 0;
  PORTD &= ~(PORTD_LINES_MASK); 
  PORTD |= m_rowMaskNow;

  // Init column related variables
  m_columnNow = PIND & PORTD_COLUMN_MASK;

  for(int i=0; i<4; i++)
    m_columnsOld[i] = PORTD_COLUMN_MASK;
}

Keyboard::~Keyboard()
{
}

char Keyboard::readRow()
{
  m_columnNow = PIND & PORTD_COLUMN_MASK;
  
  // checks if there is any change in the columns.
  if(m_columnsOld[m_rowCount] != m_columnNow)
  {    
    deboucing();
    m_columnNow = PIND & PORTD_COLUMN_MASK; // se comentar nao muda nada, sei la pq raios.
    m_columnsOld[m_rowCount] = m_columnNow;
    switch (m_columnNow)
    {
      case COLUNA_0: 
        switch (m_rowMaskNow)
        {
          case LINHA_0:
            return('1');
            break;
          case LINHA_1:
            return('4');
            break;
          case LINHA_2:
            return('7');
            break;
          case LINHA_3:
            return('*');
          default:
            break;
        }
        break;

      case COLUNA_1: 
        switch (m_rowMaskNow)
        {
          case LINHA_0:
            return('2');
            break;
          case LINHA_1:
            return('5');
            break;
          case LINHA_2:
            return('8');
            break;
          case LINHA_3:
            return('0');
            break;
          default:
            break;
        }
        break;
      case COLUNA_2:
        switch (m_rowMaskNow)
        {
          case LINHA_0:
            return('3');
            break;
          case LINHA_1:
            return('6');
            break;
          case LINHA_2:
            return('9');
            break;
          case LINHA_3:
            PORTC =1;
            return('#');
          break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }   
  return 0;
}

void Keyboard::nextRow()
{
  switch (m_rowMaskNow)
  {
  case LINHA_0:
    m_rowMaskNow = LINHA_1;
    m_rowCount=1;
    break;
  case LINHA_1:
    m_rowMaskNow = LINHA_2;
    m_rowCount=2;
    break;
  case LINHA_2:
    m_rowMaskNow = LINHA_3;
    m_rowCount=3; 
    break;
  case LINHA_3:
    m_rowMaskNow = LINHA_0;
    m_rowCount=0;
    break;
  default:
    m_rowMaskNow = LINHA_0;
    m_rowCount=0;
    break;
  }

  PORTD &= ~(PORTD_LINES_MASK); 
  PORTD |= m_rowMaskNow;
}

// Função que faz o deboucing
void Keyboard::deboucing()
{
	unsigned char count = 0,  
                b_antigo = m_columnNow,
                b_novo;
  
	do
  {

    timer_us(10000);

		b_novo = PORTD & PORTD_COLUMN_MASK;

		if(b_novo == b_antigo)
    {
			count++;
		}
    else
    {
			count = 0;
		}

		b_antigo = b_novo;

	}while(count < BOUNCE);
}