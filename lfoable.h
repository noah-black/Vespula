#ifndef LFOABLE_H
#define LFOABLE_H

#include <vector>
#include "lfoconnection.h"

class Lfoable {
    public:
        ~Lfoable();
        void addLfoConnection(LfoConnection* lfoConnection);
        double getLfoPosition();
        void setLfoAmount(double amount);
    private:
        vector<LfoConnection*> lfoConnections;
};

#endif
