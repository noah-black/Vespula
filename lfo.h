#ifndef LFO_H
#define LFO_H

#include "oscillator.h"
#include "oscillators.h"
#include <set>

using namespace std;

class LFO {
    public:
        LFO(WaveTable *waveTable);
        double getPos();
        void advance();
        void setFreq(double freq);
        void setWaveform(waveformType waveform);
    private:
        waveformType waveform;
        Oscillator oscillator;
        double position;
};

#endif
