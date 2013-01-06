#include "oscillator.h"
#include <stdio.h>
using namespace std;

Oscillator::Oscillator(WaveTable *waveTable, waveformType *waveform, double freq) :
    waveTable(waveTable)
{
    this->waveform = waveform;
	period = SAMPLE_RATE/freq;
    phase = 0;
    pthread_mutex_init(&setFreqMutex, NULL);
}

void Oscillator::setFreq(double freq) {
    double newPeriod;
	newPeriod = SAMPLE_RATE/freq;
    pthread_mutex_lock(&setFreqMutex);
    phase = phase * (newPeriod/period);
    period = newPeriod;
    pthread_mutex_unlock(&setFreqMutex);
}

void Oscillator::advance() {
	phase += 1;
    if(phase >= period) {
        phase -= period;
    }
}

double Oscillator::getSample() {
    double sample;
    pthread_mutex_lock(&setFreqMutex);
    sample = (waveTable->*(*waveform))(phase, SAMPLE_RATE/period);
	advance();
    pthread_mutex_unlock(&setFreqMutex);
    return sample;
}
