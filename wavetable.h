#ifndef WAVETABLE_H
#define WAVETABLE_H

#include <vector>

#define NUM_NOTES 84
#define MIDDLE_A_INDEX 36
#define ALIASING_THRESHOLD 110

class WaveTable {
public:
  WaveTable();
  ~WaveTable();
  double triangle(double phase, double freq);
  double square(double phase, double freq);
  double sawtooth(double phase, double freq);
  double sine(double phase, double freq);
  static double getSample(double phase, double freq, double **table);
  void buildTriangle();
  void buildSquare();
  void buildSawtooth();
  double sawtoothFunction(double phase, double f);
  double squareFunction(double phase, double f);
  double triangleFunction(double phase, double f);

private:
  double *triangleTable[NUM_NOTES];
  double *squareTable[NUM_NOTES];
  double *sawtoothTable[NUM_NOTES];
};

#endif
