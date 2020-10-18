#ifndef LCD_H
#define LCD_H

#define CLEAR_DISPLAY          0x01
#define CURSOR_HOME            0x02
#define ENTRY_SET_MODE         0x06
#define DISPLAY_CONTROL        0x0C
#define CURSOR_DISPLAY_SHIFT   0x17
#define FUNCTION_SET           0x28

#define MAX_STRING_SIZE 16

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