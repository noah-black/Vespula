#include "lfo.h"
#include <stdio.h>

LFO::LFO(WaveTable *waveTable)
    : oscillator(waveTable, &WaveTable::sawtooth, 0.5) {
  position = 0;
}

double LFO::getPos() { return position; }

void LFO::advance() { position = oscillator.getSample(); }

void LFO::setFreq(double freq) { oscillator.setFreq(freq); }

void LFO::setWaveform(waveformType waveform) {
  oscillator.setWaveform(waveform);
}
