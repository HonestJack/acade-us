/*
 * Projeto.cpp
 *
 * Created: 05/10/2020 18:07:40
 * Author : Carlo, Iago, Murilo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


#define CLEAR_DISPLAY          0x01
#define CURSOR_HOME            0x02
#define ENTRY_SET_MODE         0x06
#define DISPLAY_CONTROL        0x0C
#define CURSOR_DISPLAY_SHIFT   0x17
#define FUNCTION_SET           0x28

#define TIMER_0_8bits  0x02
#define TIMER_0_16bits 0x01

#define MAX_STRING 16

#define BOUNCE 8


class c_relogio
{
	public:
		volatile unsigned int counter = 0;
		float return_horas(){
			return((float)counter/60);
		}
		
};

c_relogio relogio;

ISR (TIMER1_COMPA_vect)
{
	TIFR1 |= (1 << 1); // Clear Flag
	relogio.counter++;
}

void timer_40ums(){
	TCCR0A = 2;        // Timer modo CTC
	TCCR0B = 2;        // Prescaler 64
	TCNT0  = 0;        // Zera o timer
	OCR0A =	80;	   // 40u/(0.0625u*presc)
	TIFR0 |= (1 << 0); // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}

void timer_1_64ms(){
	TCCR0A = 2;        // Timer modo CTC
	TCCR0B = 4;        // Prescaler 256
	TCNT0  = 0;        // Zera o timer
	OCR0A =	103;	   // 1640u/(0.0625u*presc)
	TIFR0 |= (1 << 0); // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}

void timer_1ms(){
	TCCR0A = 2;        // Timer modo CTC
	TCCR0B = 3;        // Prescaler 64
	TCNT0  = 0;        // Zera o timer
	OCR0A =	250;	   // 1000u/(0.625u*presc)
	TIFR0 |= (1 << 0); // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}


void lcd_function(char function){
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
		timer_40ums();
		} else{
		timer_1_64ms();
	}
	
}
void init_display(){
	
	PORTD &= ~(1 << 7); // RS = 0
	PORTB |=  (1 << 4); // E = 1
	PORTB &= 0xF0;
	PORTB |= (0x02 & 0x0F);
	PORTB &= ~(1 << 4); // E = 0
	timer_40ums();
	
	lcd_function(FUNCTION_SET);
	lcd_function(ENTRY_SET_MODE);
	lcd_function(DISPLAY_CONTROL);
	lcd_function(CURSOR_DISPLAY_SHIFT);
	lcd_function(CLEAR_DISPLAY);
}

void print_string(char string[MAX_STRING+1]){
	unsigned char n = 0;
	PORTD |=  (1 << 7); // RS  = 1
	while(string[n] != '\0'){
		lcd_function(string[n]);
		n++;
	}
	PORTD &= ~(1 << 7); // RS = 0
}

void init()
{
	DDRB  = 0xFF;   // PB como saída
	DDRD  = 0xFF;   // PD como saída
	TCCR1A = 4;        // Timer modo CTC
	TCCR1B = 4;        // Prescaler 256
	OCR1A  = 0;        //  1 000 000u/(0.0625u*presc)
	TIFR1 |= (1 << 1); // Clear Flag
	TIMSK1 = (1 << 1); // Ativa interrupt do Timer1 na comparação
	sei();
}

void tempo()
{
	TCNT1  = 162;      // 256 - 3000u/(0.5u*presc)
	TIFR1 |= (1 << 0); // Clear Flag
	while(!(TIFR0 & (1 << 0)))
	{
		
	}
}


int main(void)
{
	init();
	init_display();
	print_string("Ola Caralho");
    while (1) 
    {
    }
}

