#include "wavetable.h"
#include "soundprocessor.h"
#include <cmath>
#include <stdio.h>

#define EPSILON 0.001

WaveTable::WaveTable() {
  buildSawtooth();
  buildSquare();
  buildTriangle();
}

WaveTable::~WaveTable() {
  int i;
  for (i = 0; i < NUM_NOTES; i++) {
    delete[] triangleTable[i];
    delete[] sawtoothTable[i];
    delete[] squareTable[i];
  }
}

double WaveTable::triangle(double phase, double freq) {
  if (freq < ALIASING_THRESHOLD) {
    double t = phase * freq / SAMPLE_RATE;
    return pow(-1, (int)floor(t + 0.5)) * ((t * 2) - 1);
  }
  return getSample(phase, freq, triangleTable);
}
double WaveTable::square(double phase, double freq) {
  if (freq < ALIASING_THRESHOLD) {
    return (phase * freq / SAMPLE_RATE) < 0.5 ? 0 : 1;
  }
  return getSample(phase, freq, squareTable);
}

double WaveTable::sawtooth(double phase, double freq) {
  if (freq < ALIASING_THRESHOLD) {
    double t = phase * freq / SAMPLE_RATE;
    return (t - floor(t + 0.5)) * 2;
  } else
    return getSample(phase, freq, sawtoothTable);
}

double WaveTable::getSample(double phase, double freq, double **table) {
  double closestFreq, ratio, sample, cursor, period, amountRead, amountLeft;
  int closest, index;
  sample = 0;
  freq = roundf(freq * 100.0f) / 100.0f;
  closest = (int)floor(12 * (log(freq) / 440) / log(2)) + MIDDLE_A_INDEX;
  closest = closest >= NUM_NOTES ? NUM_NOTES - 1 : (closest < 0 ? 0 : closest);
  closestFreq = 440 * pow(2, (double(closest - MIDDLE_A_INDEX)) / 12);
  period = SAMPLE_RATE / closestFreq;
  if (fabs((closestFreq - freq) / closestFreq) < EPSILON) {
    ratio = 1;
  } else
    ratio = freq / closestFreq;
  amountRead = 0;
  cursor = ratio * phase;
  while (fabs((amountRead - ratio)) / ratio > EPSILON && amountRead < ratio) {
    cursor = fmod(cursor, period);
    amountLeft = std::min(
        std::min(1.0, ratio - amountRead),
        std::min(ratio - amountRead,
                 std::min(period - cursor,
                          (fabs((fmod(cursor, 1)) < EPSILON) ? cursor + 1
                                                             : ceil(cursor)) -
                              cursor)));
    index = (int)floor(cursor);
    amountRead += amountLeft;
    cursor += amountLeft;
    sample += amountLeft * table[closest][index];
  }
  return sample / ratio;
}

double WaveTable::sine(double phase, double freq) {
  return sin(((phase * freq) / SAMPLE_RATE) * 2 * PI);
}

void WaveTable::buildTriangle() {
  int i, j;
  double freq, period;
  for (i = 0; i < NUM_NOTES; i++) {
    freq = 440 * pow(2, (double(i - MIDDLE_A_INDEX)) /
                            12); // sawtoothTable[MIDDLE_A_INDEX] = A440
    period = SAMPLE_RATE / freq;
    triangleTable[i] = new double[(int)ceil(period)];
    for (j = 0; j < ceil(period); j++) {
      triangleTable[i][j] = triangleFunction(j, freq);
    }
  }
}

void WaveTable::buildSquare() {
  int i, j;
  double freq, period;
  for (i = 0; i < NUM_NOTES; i++) {
    freq = 440 * pow(2, (double(i - MIDDLE_A_INDEX)) /
                            12); // sawtoothTable[MIDDLE_A_INDEX] = A440
    period = SAMPLE_RATE / freq;
    squareTable[i] = new double[(int)ceil(period)];
    for (j = 0; j < ceil(period); j++) {
      squareTable[i][j] = squareFunction(j, freq);
    }
  }
}

void WaveTable::buildSawtooth() {
  int i, j;
  double freq, period;
  for (i = 0; i < NUM_NOTES; i++) {
    freq = 440 * pow(2, (double(i - MIDDLE_A_INDEX)) /
                            12); // sawtoothTable[MIDDLE_A_INDEX] = A440
    period = SAMPLE_RATE / freq;
    sawtoothTable[i] = new double[(int)ceil(period)];
    for (j = 0; j < (int)ceil(period); j++) {
      sawtoothTable[i][j] = sawtoothFunction(j, freq);
    }
  }
}

double WaveTable::sawtoothFunction(double phase, double f) {
  double t, sum, sample;
  int i;
  t = phase / SAMPLE_RATE;
  sum = 0;
  for (i = 1; i < SAMPLE_RATE / (2 * f); i++) {
    sum += pow(-1, i + 1) * sin(2 * PI * i * f * t) / i;
  }
  sample = (2 * sum) / (PI);
  return sample;
}

double WaveTable::squareFunction(double phase, double f) {
  double t, sum, sample;
  int i;
  t = phase / SAMPLE_RATE;
  sum = 0;
  for (i = 1; i < (SAMPLE_RATE / 4) / f; i++) {
    sum += sin(2 * PI * (2 * i - 1) * f * t) / (2 * i - 1);
  }
  sample = (4 * sum) / PI;
  return sample;
}

double WaveTable::triangleFunction(double phase, double f) {
  double t, sum, sample;
  int i;
  t = phase / SAMPLE_RATE;
  sum = 0;
  for (i = 0; i < (SAMPLE_RATE / 4) / f; i++) {
    sum += pow(-1, i) * sin((2 * i + 1) * 2 * PI * f * t) / pow(2 * i + 1, 2);
  }
  sample = (8 * sum) / (pow(PI, 2));
  return sample;
}
