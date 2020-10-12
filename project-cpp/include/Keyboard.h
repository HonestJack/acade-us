#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
public:
  Keyboard(/* args */);
  ~Keyboard();

  char readRow();
  void nextRow();

private:
  void deboucing();

  unsigned char m_rowMaskNow;
  unsigned char m_rowCount;

  unsigned char m_columnsOld[4];
  unsigned char m_columnNow;
};

#endif