#ifndef TIMER_H
#define TIMER_H

#define START_HOUR    13
#define START_MINUTE  30
#define START_SECOND  0
#define START_TIME    (START_HOUR*(long)3600 + START_MINUTE*(long)60 + START_SECOND)

#define HORAS_EM_UM_DIA (long)24*60*60
#define HORA_DE_ABRIR   (long)7*60*60
#define HORA_DE_FECHAR  (long)23*60*60

class Timer
{
public:
  Timer(/* args */);
  ~Timer();

  volatile long getTime();
  void setTime(long newTime);
  bool is_open();
// private:
  volatile static long counter;
  volatile static short aux_counter;
};

#endif