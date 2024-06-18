#include "oscillators.h"
#include <stdio.h>

double Oscillators::triangle(double phase, double period) {
  return (fabs(((phase * 4) / period) - 2.0) - 1.0);
}

double Oscillators::sawtooth(double phase, double period) {
  //	return (phase < period*0.99) ? (((phase/(period*0.99)) * 2) - 1) :
  //((((phase - (period*0.99))/(period*(0.01))) * -2) + 1);
  double f, t, sum, sample;
  int i, stopAt;
  t = phase / SAMPLE_RATE;
  f = SAMPLE_RATE / period;
  sum = 0;
  for (i = 1; i < SAMPLE_RATE / (2 * f); i++) {
    sum += (i % 2 == 1 ? 1 : -1) * sin(2 * PI * i * f * t) / i;
  }
  sample = (2 * sum) / PI;
  return sample;
}

double Oscillators::square(double phase, double period) {
  //	return ((phase > (period / 2)) ? 1 : -1);
  double f, t, sum, sample;
  int i;
  t = phase / SAMPLE_RATE;
  f = SAMPLE_RATE / period;
  sum = 0;
  for (i = 1; i < (SAMPLE_RATE / 2) / f; i += 2) {
    sum += (i % 2 == 1 ? 1 : -1) * sin(2 * PI * i * f * t) / i;
  }
  sample = (2 * sum) / PI;
  return sample;
}

double Oscillators::sine(double phase, double period) {
  return sin((phase / period) * 2 * PI);
}
