#include "Lcd.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#define CLEAR_DISPLAY          0x01
#define CURSOR_HOME            0x02
#define ENTRY_SET_MODE         0x06
#define DISPLAY_CONTROL        0x0C
#define CURSOR_DISPLAY_SHIFT   0x17
#define FUNCTION_SET           0x28

#define MAX_STRING 16

Lcd::Lcd(/* args */)
{
  PORTD &= ~(1 << 7); // RS = 0
  PORTB |=  (1 << 4); // E = 1
  PORTB &= 0xF0;
  PORTB |= (0x02 & 0x0F);
  PORTB &= ~(1 << 4); // E = 0
  timer_us(40);
  
  lcd_function(FUNCTION_SET);
  lcd_function(ENTRY_SET_MODE);
  lcd_function(DISPLAY_CONTROL);
  lcd_function(CURSOR_DISPLAY_SHIFT);
  lcd_function(CLEAR_DISPLAY);
}

Lcd::~Lcd()
{
}

void Lcd::print(char ch)
{
  PORTD |=  (1 << 7); // RS  = 1
  lcd_function(ch);
  PORTD &= ~(1 << 7); // RS  = 0
}

void Lcd::print(char string[])
{
  unsigned char n = 0;
  PORTD |=  (1 << 7); // RS  = 1
  while(string[n] != '\0'){
    lcd_function(string[n]);
    n++;
  }
  PORTD &= ~(1 << 7); // RS = 0
}

void Lcd::clear()
{
  lcd_function(CLEAR_DISPLAY);
}

void Lcd::lcd_function(char function){
		//P1 &= ~(1 << 3); // RS = 0
	
		PORTB |=  (1 << 4); // E = 1
		PORTB &= 0xF0;
		PORTB |= ((function >> 4) & 0x0F);
		PORTB &= ~(1 << 4); // E = 0
	
		PORTB |=  (1 << 4); // E = 1
		PORTB &= 0xF0;
		PORTB |= (function & 0x0F);
		PORTB &= ~(1 << 4); // E = 0
	
		if(function != CLEAR_DISPLAY){
			timer_us(40);
			} else{
			timer_us(1640);
		}
	}

char Lcd::convert_int2string(int var)
{
  switch (var)
	{
		case 0:
			return '0';
			break;
		case 1:
			return '1';
			break;
		case 2:
			return '2';
			break;
		case 3:
			return '3';
			break;
		case 4:
			return '4';
			break;
		case 5:
			return '5';
			break;
		case 6:
			return '6';
			break;
		case 7:
			return '7';
			break;
		case 8:
			return '8';
			break;
		case 9:
			return '9';
			break;
		default:
			return '0';
	}
}

void Lcd::timer_us(unsigned short tempo){
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