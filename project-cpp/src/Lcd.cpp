#include "Lcd.h"

#include "utils.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>



Lcd::Lcd(/* args */)
{
  DDRB   = 0xFF;   // PB como saida

	DDRD |=  (1 << 7);   // PD.7 como saida - R/S do display

  PORTD &= ~(1 << 7); // RS = 0
  PORTB |=  (1 << 4); // E = 1
  PORTB &= 0xF0;
  PORTB |= (0x02 & 0x0F);
  PORTB &= ~(1 << 4); // E = 0
  delay_us(40);
  
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

void Lcd::lcd_function(char function)
{
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
		delay_us(40);
		} else{
		delay_us(1640);
	}
}	