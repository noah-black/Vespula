#ifndef FM_H
#define FM_H

#include "envelopeconnection.h"
#include "lfoable.h"
#include "modulatable.h"
#include "oscillator.h"
#include <vector>

class FM : public Oscillator, public Modulatable, public Lfoable {
public:
  FM(WaveTable *waveTable, waveformType waveform, double freq, double *depth);
  double getSample();
  void setFreq(double freq);
  void setDepth(double i);
  void modulate(double amount);

private:
  double *depth;
  double carrierPhase;
  double envelopeModifier;
};

#endif
