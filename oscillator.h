#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "envelope.h"
#include "soundprocessor.h"
#include "wavetable.h"
#include <string>

class Oscillator : public SoundProcessor {
public:
  Oscillator(WaveTable *waveTable, waveformType waveform, double freq);
  virtual void setFreq(double freq);
  void setWaveform(waveformType waveform);
  virtual double getSample();

protected:
  WaveTable *waveTable;
  void advance();
  double phase;
  double period;
  pthread_mutex_t setFreqMutex;
  pthread_mutex_t setWaveformMutex;
  waveformType waveform;
};
#endif
