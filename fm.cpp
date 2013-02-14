#include "fm.h"
#include <stdio.h>

FM::FM(WaveTable *waveTable, waveformType waveform, double freq, double *depth) : Oscillator(waveTable, waveform, freq) {
	this->depth = depth;
	carrierPhase = 0;
    envelopeModifier = 0;
}

double FM::getSample() {
	double in, out, freq, currentDepth;
    pthread_mutex_lock(&setFreqMutex);
    currentDepth = *depth + envelopeModifier + (getLfoPosition()*10000);
    currentDepth = currentDepth < 0 ? 0 : currentDepth;
    freq = SAMPLE_RATE/period;
    in = ((waveTable)->*(waveform))(phase, SAMPLE_RATE/period);
	out = sin(2*PI*(carrierPhase/period));
	carrierPhase = fmod((carrierPhase+1+(((currentDepth)*in)/freq)), period);
    advance();
    pthread_mutex_unlock(&setFreqMutex);
	return out;
}

void FM::modulate(double amount) {
    envelopeModifier = amount*10000;
}

void FM::setFreq(double freq) {
    double newPeriod;
	newPeriod = SAMPLE_RATE/freq;
    pthread_mutex_lock(&setFreqMutex);
    phase = phase * (newPeriod/period);
    carrierPhase = carrierPhase * (newPeriod/period);
    period = newPeriod;
    pthread_mutex_unlock(&setFreqMutex);
}
