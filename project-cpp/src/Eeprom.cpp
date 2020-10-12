// #include "Eeprom.h"

// #include <avr/io.h>
// #include <avr/interrupt.h>

// Eeprom::Eeprom(/* args */)
// {
// }

// Eeprom::~Eeprom()
// {
// }

// void Eeprom::write(unsigned int uiAddress, unsigned char ucData)
// {
// /* Wait for completion of previous write */
 
//   while(EECR & (1<<eewe));
  
//   /* Set up address and data registers */
  
//   EEAR = uiAddress;
  
//   EEDR = ucData;
  
//   /* Write logical one to EEMWE */
  
//   EECR |= (1<<eemwe);
  
//   /* Start eeprom write by setting EEWE */
  
//   EECR |= (1<<eewe);
// }

// void Eeprom::read()
// {
  
// }