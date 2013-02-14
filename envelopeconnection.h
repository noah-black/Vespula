#ifndef ENVELOPE_CONNECTION_H
#define ENVELOPE_CONNECTION_H

#include "envelope.h"
#include "modulatable.h"

using namespace std;

class EnvelopeConnection {
    public:
        EnvelopeConnection(Envelope *envelope, Modulatable *target, double *amount);
        void notify(int samplesElapsed, double velocity);
        void notify(int samplesElapsed, int releaseSample, double velocity);
    private:
        Envelope *envelope;
        Modulatable *target;
        double *amount;
};

#endif
