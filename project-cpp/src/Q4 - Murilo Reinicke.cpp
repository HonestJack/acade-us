#include <avr/io.h>
#include <avr/interrupt.h>

volatile long counter;
volatile long alarme_counter;
volatile long aux_counter;
volatile char contador_digitos;
volatile char alarme;
volatile char senha_correta;
volatile char sensor_acionado;

static long key_value;

volatile unsigned char m_rowMaskNow;
volatile unsigned char m_rowCount;

volatile unsigned char m_columnsOld[4];
volatile unsigned char m_columnNow;

#define DIGIT_NUMBER 7
#define ASCII_SHIFT 48

#define ASTERIX 10

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

#define BOUNCE 8

void delay_us(unsigned short tempo){
	unsigned short presc;
	TCCR0A = 2;        // Timer modo CTC
	
	if (tempo <= 128)
	{
		TCCR0B = 2;        // Prescaler 8
		presc = 8;
	}else if(tempo <= 1024)
	{
		TCCR0B = 3;        // Prescaler 64
		presc = 64;
	}else
	{
		TCCR0B = 4;        // Prescaler 256
		presc = 256;
	}
	
	TCNT0  = 0;                    // Zera o timer
	OCR0A =	tempo/(0.0625*presc);  // 1000u/(0.625u*presc)
	TIFR0 |= (1 << 0);             // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}

void delay_ms(unsigned short tempo)
{
for (unsigned short i = 0; i < tempo; i++)
{
	delay_us(1000);
}

}

short pot(short base, short potencia)
{
  short valor = 1;
  unsigned char i;
  for(i=0; i<potencia; i++)
  {
    valor = valor*base;
  }
  base = 4;
  return valor;
}



char readRow()
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
            return(ASTERIX);
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

void nextRow()
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
void deboucing()
{
	unsigned char count = 0,  
                b_antigo = m_columnNow,
                b_novo;
  
	do
  {

    delay_us(10000);

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

unsigned short reading()
{
  unsigned char key;
  short value = 0;
  key = readRow();
  nextRow();

  if(key)
  {
    value = (key - ASCII_SHIFT)*pot(10,(DIGIT_NUMBER - 1 - contador_digitos));
    contador_digitos++;
  }

  return value;
}

void f_senha_correta()
{
    senha_correta = 1;
    alarme = 0;             // Desliga o alarme
    PORTB &= ~(1 << 4);
}

void le_senha(short &key_value)
{
  if(contador_digitos == DIGIT_NUMBER)
  {
    if(key_value == (2886890 + ASTERIX))
    {
      f_senha_correta();
      contador_digitos = 0;
      key_value = 0;
    }
    
  }
}



void toca_alarme()
{
    alarme = 1;
}

ISR (TIMER1_OVF_vect) 
{
	TCNT1  = 40536; // 2^16 - 100 000u/(0.0625u*presc)
	TIFR1 |= (1 << 0); 
	aux_counter++;
    if(aux_counter >= 10) // Conta 1 segundos em dez contagens de 100ms
    {
        counter++;
        aux_counter = 0;
    }

    if(alarme)
    {
        PORTB ^= (1 << 4);
    }

    
}


void init()
{
    TCCR1A = 0;        // Timer
	TCCR1B = 3;        // Prescaler = 64
	TCCR1C = 0;
	TCNT1  = 40536;     // 2^16 - 100 000u/(0.0625u*presc)
	TIFR1 |= (1 << 0); // Clear Flag
	TIMSK1 = (1 << 0); // Ativa interrupt do Timer1


	counter = 0;
    aux_counter = 0;
    alarme_counter = 0;
    alarme = 0;
    senha_correta = 0;
    sensor_acionado = 0;

    DDRC   |=  (1 << 3);   // PC.3 como saida - Linha 0 do teclado
    DDRC   |=  (1 << 2);   // PC.2 como saida - Linha 1 do teclado
    DDRC   |=  (1 << 1);   // PC.1 como saida - Linha 2 do teclado
    DDRC   |=  (1 << 0);   // PC.0 como saida - Linha 3 do teclado

    DDRB   &= ~(1 << 0);   // PB.0 como entrada - Coluna 0 do teclado
    DDRB   &= ~(1 << 1);   // PB.1 como entrada - Coluna 1 do teclado
    DDRB   &= ~(1 << 2);   // PB.2 como entrada - Coluna 2 do teclado

    DDRB   &= ~(1 << 3);   // PB.3 como entrada - Sensor de presença

    DDRB   |=  (1 << 4);   // PB.4 como saida - Controle do alarme

    PORTD |=  (1 << 4); // Ativa pull up
    PORTD |=  (1 << 5); // Ativa pull up
    PORTD |=  (1 << 6); // Ativa pull up

    key_value = 0;
    
    contador_digitos = 0;


  m_rowMaskNow = LINHA_0;
  m_rowCount = 0;
  PORTD &= ~(PORTD_LINES_MASK); 
  PORTD |= m_rowMaskNow;


  m_columnNow = PIND & PORTD_COLUMN_MASK;

  for(int i=0; i<4; i++)
    m_columnsOld[i] = PORTD_COLUMN_MASK;

}




int main()
{
    init();
    sei();

    while(1)
    {
        if(PINB & (1 << 3) // Se o sensor for acionado
        {
            if (!sensor_acionado)
            {
               sensor_acionado = 1;
                aux_counter = counter; // Verifica o tempo em que a pessoa chegou
            }
            
            key_value += reading();
            le_senha();
            
        }else if(!alarme) // Se a pessoa saiu antes do alarme tocar
        {
            alarme_counter = counter;
            sensor_acionado = 0;
        }

        if((PINB & (1 << 3)) && ((counter - alarme_counter) >= 60) && !senha_correta) // Se a pessoa já está a mais de 60 segundos
        {
            toca_alarme();
        }

        if((!(PINB & (1 << 3))) && senha_correta) // Quando o sensor desligar e a pessoa já entrou
        {
            senha_correta = 0; // reseta o sistema
            alarme_counter = counter;
            sensor_acionado = 0;
        }
        
    }
    
}