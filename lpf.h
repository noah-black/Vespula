#ifndef LPF_H
#define LPF_H

#include "soundprocessor.h"
#include <pthread.h>

class LPF : public SoundProcessor {
public:
  LPF(SoundProcessor *input);
  double getSample();

private:
  double alpha;
  pthread_mutex_t mutexsum;
  double lastOutputSample;
  SoundProcessor *input;
  bool started;
  double phase;
  double period;
};

#endif
