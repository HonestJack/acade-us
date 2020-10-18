#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
  Timer(/* args */);
  ~Timer();

  volatile unsigned long getTime();

// private:
  volatile static unsigned long counter;
};

#endif