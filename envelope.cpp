#include "envelope.h"

Envelope::Envelope(double attack, double decay, double sustain, double release) {
    this->attack = attack;
    this->decay = decay;
    this->sustain = sustain; 
    this->release = release;
    samplesElapsed = 0;
    releaseSample = -1;
    isReleased = false;
}

double Envelope::adsFactor() {
	if (samplesElapsed < (attack * SAMPLE_RATE))
		return (samplesElapsed) / (attack * SAMPLE_RATE);
	if (samplesElapsed < ((decay+attack) * SAMPLE_RATE))
		return 1 - (((samplesElapsed-(attack*SAMPLE_RATE)) / (decay * SAMPLE_RATE)) * (1-sustain));
	return sustain;
}

double Envelope::getFactor() {
	double factor, releaseLevel;
	if(isReleased) {
		if((samplesElapsed - releaseSample) >= (release*SAMPLE_RATE))
			return 0;
		releaseLevel = adsFactor();
		factor = releaseLevel * (1 - (samplesElapsed - releaseSample) / (release * SAMPLE_RATE));
		if (factor < 0)
			factor = 0;
		if (factor > 1)
			factor = 1;
	}
    else
	    factor = adsFactor();
    samplesElapsed++;
	return factor;
}

void Envelope::setReleased() {
	if (isReleased) 
		return;
    isReleased = true;
    releaseSample = samplesElapsed;
}
