#include "oscillator.h"
#include <stdio.h>
using namespace std;

Oscillator::Oscillator(waveformType *waveform, double freq) {
    this->waveform = waveform;
	period = SAMPLE_RATE/freq;
    phase = 0;
    samples = new double[(int)ceil(period)];
    uninitialized = true;
}

Oscillator::~Oscillator() {
    delete[] samples;
}

void Oscillator::setFreq(double freq) {
	period = SAMPLE_RATE/freq;
    uninitialized = true;
}

void Oscillator::advance() {
	phase += 1;
    if(phase >= period) {
        phase -= period;
    }
}

void Oscillator::initialize() {
    int i;
    waveformType currentWaveform;
    currentWaveform = *waveform;
    for(i = 0; i < ceil(period); i++) {
        samples[i] = currentWaveform(i, period);
    }
    uninitialized = false;
}

double Oscillator::getSample() {
    double sample;
    sample = calculateSample();
        //currentWaveform = *waveform;
	//sample = currentWaveform(phase, period);
	advance();
    return sample;
}

double Oscillator::calculateSample() {
    int i, j;
    double weight;
    if(uninitialized)
        initialize();
    if(fmod(phase, 1) != 0) {
        i = floor(phase);
        if(ceil(phase) >= period) {
            j = 0;
            weight = fmod(phase, 1) / fmod(period, 1);
        }
        else {
            j = ceil(phase);
            weight = fmod(phase, 1);
        }
        return ((1-weight)*samples[i]) + (weight*samples[j]);
    }
    else
        return samples[(int)phase];
}
