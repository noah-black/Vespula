#include "lfo.h"
#include <stdio.h>

LFO::LFO(WaveTable *waveTable) :
    waveform(&WaveTable::sawtooth),
    oscillator(waveTable, &waveform, 0.5)
{ 
    position = 0;
}

double LFO::getPos() {
    return position;
}

void LFO::advance() {
    position = oscillator.getSample();
}

void LFO::setFreq(double freq) {
    printf("%f\n", freq);
    oscillator.setFreq(freq);
}

void LFO::setWaveform(waveformType waveform) {
    this->waveform = waveform;
}
