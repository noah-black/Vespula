#ifndef VIBRATO_H
#define VIBRATO_H

#include "keyboard.h"
#include "soundprocessor.h"
#include <pthread.h>
#include <vector>

class Vibrato : public SoundProcessor {
public:
  Vibrato(Keyboard **input, double period, double depth);
  double getSample();
  void setDepth(double depth);
  void setPeriod(double period);

private:
  double cursor;
  int phase;
  pthread_mutex_t mutexsum;
  int period;
  double depth;
  double lastSample;
  Keyboard **input;
};

#endif
