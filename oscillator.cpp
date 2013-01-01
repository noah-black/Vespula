#include "oscillator.h"
#include <stdio.h>
using namespace std;

Oscillator::Oscillator(waveformType *waveform, double freq) {
    this->waveform = waveform;
	period = SAMPLE_RATE/freq;
    phase = 0;
}

void Oscillator::setFreq(double freq) {
	period = SAMPLE_RATE/freq;
}

void Oscillator::advance() {
	phase += 1;
    if(phase >= period) {
        phase -= period;
    }
}

double Oscillator::getSample() {
    waveformType currentWaveform;
    double sample;
    currentWaveform = *waveform;
	sample = currentWaveform(phase, period);
	advance();
    return sample;
}
