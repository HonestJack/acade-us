#ifndef LCD_H
#define LCD_H

class Lcd
{
public:
  Lcd();
  ~Lcd();

  void print(char ch);
  void print(char string[]);

  void clear();

private:  
  void lcd_function(char function);
  char convert_int2string(int var);
  void timer_us(unsigned short tempo);
};


#endif // LCD_H