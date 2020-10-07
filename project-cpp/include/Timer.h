#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
  Timer(/* args */);
  ~Timer();

  volatile unsigned int getTime();

// private:
  volatile static unsigned int counter;
};

#endif