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

 
  void lcd_function(char function);
};


#endif // LCD_H