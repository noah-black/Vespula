#ifndef LFOABLE_H
#define LFOABLE_H

#include "lfoconnection.h"
#include <vector>

class Lfoable {
public:
  ~Lfoable();
  void addLfoConnection(LfoConnection *lfoConnection);
  double getLfoPosition();
  void setLfoAmount(double amount);

private:
  std::vector<LfoConnection *> lfoConnections;
};

#endif
