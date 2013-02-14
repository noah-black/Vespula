#ifndef LFOABLE_H
#define LFOABLE_H

#include <vector>
#include "lfoconnection.h"

class Lfoable {
    public:
        ~Lfoable();
        void addLfoConnection(LfoConnection* lfoConnection);
        double getLfoPosition();
    private:
        vector<LfoConnection*> lfoConnections;
};

#endif
