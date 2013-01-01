#ifndef ENVELOPE_CONNECTION_H
#define ENVELOPE_CONNECTION_H

#include "envelope.h"
#include "envelopable.h"

using namespace std;

class EnvelopeConnection {
    public:
        EnvelopeConnection(Envelope *envelope, Envelopable *target, double amount);
        void notify(int samplesElapsed);
        void notify(int samplesElapsed, int releaseSample);
    private:
        Envelope *envelope;
        Envelopable *target;
        double amount;
};

#endif
