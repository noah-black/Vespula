#ifndef FILTER_H
#define FILTER_H

#include <lfoable.h>
#include <pthread.h>
#include <soundeffect.h>
#include <stdlib.h>

class Filter : public SoundEffect, public Lfoable {
public:
  Filter();
  virtual double getSample(double in);
  void setCutoff(double cutoff);
  void setResonance(double resonance);
  virtual double getCutoff();
  virtual double getResonance();

protected:
  double resonance, cutoff;
  void updateCoef();

private:
  double getCutoffHz(double cutoff);
  pthread_mutex_t myMutex;
  double a0, a1, a2, b1, b0, i1, i2, o1, o2, i1p, i2p, o1p, o2p, ql, qp, a0p,
      a1p, a2p, b0p, b2p;
};

#endif
