#ifndef LFO_CONNECTION_H
#define LFO_CONNECTION_H

#include "lfo.h"

class LfoConnection {
public:
  LfoConnection(LFO *target, double amount);
  void setAmount(double amount);
  double getPos();

private:
  LFO *target;
  double amount;
};

#endif
