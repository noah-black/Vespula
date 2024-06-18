#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "soundprocessor.h"

class Envelope {
public:
  Envelope(double attack, double decay, double sustain, double release);
  void setAttack(double value);
  void setDecay(double value);
  void setSustain(double value);
  void setRelease(double value);
  double getFactor(int samplesElapsed);
  double getFactor(int samplesElapsed, int releaseSample);
  bool isDead(int samplesElapsed, int releaseSample);

private:
  double adsFactor(int samplesElapsed);
  double attack;
  double decay;
  double sustain;
  double release;
};
#endif
