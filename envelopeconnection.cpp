#include "envelopeconnection.h"

EnvelopeConnection::EnvelopeConnection(Envelope *envelope, Modulatable *target, double *amount) : 
envelope(envelope), 
target(target), 
amount(amount) 
{}

void EnvelopeConnection::notify(int samplesElapsed) {
    double factor = envelope->getFactor(samplesElapsed);
    target->modulate(factor*(*amount));
}

void EnvelopeConnection::notify(int samplesElapsed, int releaseSample) {
    double factor = envelope->getFactor(samplesElapsed, releaseSample);
    target->modulate(factor*(*amount));
}
