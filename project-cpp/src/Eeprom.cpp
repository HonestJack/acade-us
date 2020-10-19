#include "Eeprom.h"

#include <avr/io.h>
#include <avr/interrupt.h>

Eeprom::Eeprom(/* args */)
{
  m_size = 0;
}

Eeprom::~Eeprom()
{
}

unsigned char Eeprom::at(unsigned int index)
{
  return readByte(index);
}

void Eeprom::append(unsigned char data)
{
  writeByte(m_size,data);
  m_size++;
}

void Eeprom::writeByte(unsigned int addr, unsigned char data)
{
  cli(); // Disable interrupts

  while(EECR & (1<<EEPE)); // Wait for completion of previous write 
  
  // Set up address and data registers  
  EEAR = addr;  
  EEDR = data;
  
  EECR |= (1<<EEMPE); //Write logical one to EEMPE 
  
  EECR |= (1<<EEPE);   //Start eeprom write by setting EEWE

  sei(); // Enable interrupts
}

unsigned char Eeprom::readByte(unsigned int addr)
{
  cli(); // Disable interrupts

  while(EECR & (1<<EEPE)); //Wait for completion of previous write 

  // Set up address and data registers
  EEAR = addr;

  EECR |= (1<<EERE); // Start eeprom read by setting EERE

  sei(); // Enable interrupts

  return EEDR;
}