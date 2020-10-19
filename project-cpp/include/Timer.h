#ifndef TIMER_H
#define TIMER_H

#define START_HOUR    13
#define START_MINUTE  30
#define START_SECOND  0
#define START_TIME    (START_HOUR*(long)3600 + START_MINUTE*(long)60 + START_SECOND)

class Timer
{
public:
  Timer(/* args */);
  ~Timer();

  volatile long getTime();
  void setTime(volatile long newTime);
// private:
  volatile static long counter;
};

#endif