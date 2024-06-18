#ifndef SP_H
#define SP_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0
#define PI 3.14159265358979323846

#include "wavetable.h"
#include <math.h>

typedef double (WaveTable::*waveformType)(double, double);

enum note {
  n1,
  s1,
  n2,
  s2,
  n3,
  n4,
  s4,
  n5,
  s5,
  n6,
  s6,
  n7,
  n8,
  s8,
  n9,
  s9,
  n10,
  n11,
  s11,
  n12,
  s12,
  n13,
  s13,
  n14,
  n15,
  s15,
  n16,
  s16
};

class SoundProcessor {
public:
  virtual double getSample() = 0;
};

#endif
