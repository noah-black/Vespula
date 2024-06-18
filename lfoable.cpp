#include "lfoable.h"

void Lfoable::addLfoConnection(LfoConnection *lfoConnection) {
  lfoConnections.push_back(lfoConnection);
}

Lfoable::~Lfoable() {
  std::vector<LfoConnection *>::iterator it;
  for (it = lfoConnections.begin(); it != lfoConnections.end(); ++it) {
    delete (*it);
  }
}

double Lfoable::getLfoPosition() {
  double lfoModifier;
  lfoModifier = 0;
  std::vector<LfoConnection *>::iterator it;
  for (it = lfoConnections.begin(); it != lfoConnections.end(); ++it) {
    lfoModifier += (*it)->getPos();
  }
  return lfoModifier;
}

void Lfoable::setLfoAmount(double amount) {
  std::vector<LfoConnection *>::iterator it;
  for (it = lfoConnections.begin(); it != lfoConnections.end(); ++it) {
    (*it)->setAmount(amount);
  }
}
