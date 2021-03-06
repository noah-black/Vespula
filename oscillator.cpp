#include "oscillator.h"
#include <stdio.h>
using namespace std;

Oscillator::Oscillator(WaveTable *waveTable, waveformType waveform, double freq) :
    waveTable(waveTable)
{
    this->waveform = waveform;
	period = SAMPLE_RATE/freq;
    phase = 0;
    pthread_mutex_init(&setFreqMutex, NULL);
    pthread_mutex_init(&setWaveformMutex, NULL);
}

void Oscillator::setFreq(double freq) {
    pthread_mutex_lock(&setFreqMutex);
    double newPeriod;
	newPeriod = SAMPLE_RATE/freq;
    phase = phase * (newPeriod/period);
    period = newPeriod;
    pthread_mutex_unlock(&setFreqMutex);
}

void Oscillator::advance() {
	phase += 1;
    if(phase >= period-0.001) {
        phase -= period;
    }
}

double Oscillator::getSample() {
    pthread_mutex_lock(&setFreqMutex);
    double sample;
    pthread_mutex_lock(&setWaveformMutex);
    sample = (waveTable->*waveform)(phase, SAMPLE_RATE/period);
    pthread_mutex_unlock(&setWaveformMutex);
	advance();
    pthread_mutex_unlock(&setFreqMutex);
    return sample;
}

void Oscillator::setWaveform(waveformType waveform) {
    pthread_mutex_lock(&setWaveformMutex);
    this->waveform = waveform;
    pthread_mutex_unlock(&setWaveformMutex);
}
