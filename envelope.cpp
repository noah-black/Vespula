#include "envelope.h"

Envelope::Envelope(double attack, double decay, double sustain, double release) {
    this->attack = attack;
    this->decay = decay;
    this->sustain = sustain; 
    this->release = release;
}

double Envelope::adsFactor(int samplesElapsed) {
	if (samplesElapsed < (attack * SAMPLE_RATE))
		return ((double)samplesElapsed) / (attack * SAMPLE_RATE);
	if (samplesElapsed < ((decay+attack) * SAMPLE_RATE)) {
		return sustain + (1-sustain)*(pow(1-((double)(samplesElapsed-(attack*SAMPLE_RATE)) / (decay * SAMPLE_RATE)), 2));
    }
	return sustain;
}

double Envelope::getFactor(int samplesElapsed) {
	double factor;
	factor = adsFactor(samplesElapsed);
	return factor;
}

double Envelope::getFactor(int samplesElapsed, int releaseSample) {
    double factor, releaseLevel;
    if((samplesElapsed - releaseSample) >= (release*SAMPLE_RATE))
        return 0;
    releaseLevel = adsFactor(samplesElapsed);
    factor = releaseLevel * (1 - (samplesElapsed - releaseSample) / (release * SAMPLE_RATE));
    if (factor < 0)
        factor = 0;
    if (factor > 1)
        factor = 1;
    return factor;
}

void Envelope::setAttack(double value) {
    attack = value;
}

void Envelope::setDecay(double value) {
    decay = value;
}

void Envelope::setSustain(double value) {
    sustain = value;
}

void Envelope::setRelease(double value) {
    release = value;
}

bool Envelope::isDead(int samplesElapsed, int releaseSample) {
	return ((samplesElapsed - releaseSample) > (release * SAMPLE_RATE));
}

