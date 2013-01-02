#include "fm.h"
#include <stdio.h>

FM::FM(waveformType *waveform, double freq, double *depth) : Oscillator(waveform, freq) {
	this->depth = depth;
	carrierPhase = 0;
    envelopeModifier = 0;
}

double FM::getSample() {
	double in, out, freq, currentDepth;
    currentDepth = *depth + envelopeModifier;
    waveformType currentWaveform = *waveform;
    freq = SAMPLE_RATE/period;
	in = currentWaveform(phase, period);
	out = sin(2*PI*(carrierPhase/period));
	carrierPhase = fmod((carrierPhase+1+(((currentDepth)*in)/freq)), period);
    advance();
	return out;
}

void FM::envelopeUpdate(double amount) {
    envelopeModifier = amount*10000;
}
