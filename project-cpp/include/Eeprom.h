#ifndef EEPROM_H
#define EEPROM_H

class Eeprom
{
public:
  Eeprom();
  ~Eeprom();

  unsigned char at(unsigned int index);
  void append(unsigned char data);
  void escreve(unsigned int addr, unsigned char data);

private:
  void writeByte(unsigned int addr, unsigned char data);
  unsigned char readByte(unsigned int addr);

  unsigned int m_size;
};

#endif