#include "filterproxy.h"
#include <stdio.h>

FilterProxy::FilterProxy(Filter *filter) : filter(filter) {
  cutoff = filter->getCutoff();
  resonance = filter->getResonance();
  cutoffMod = 0;
  updateCoef();
}

double FilterProxy::getCutoff() {
  double cutoffPos;
  cutoffPos = cutoffMod + filter->getCutoff() + filter->getLfoPosition();
  cutoffPos = cutoffPos > 1 ? 1 : cutoffPos < 0 ? 0 : cutoffPos;
  return cutoffPos;
}

double FilterProxy::getResonance() { return filter->getResonance(); }

void FilterProxy::modulate(double amount) { cutoffMod = amount; }

double FilterProxy::getSample(double input) {
  updateCoef();
  return Filter::getSample(input);
}
