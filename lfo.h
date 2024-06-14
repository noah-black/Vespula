#ifndef LFO_H
#define LFO_H

#include "oscillator.h"
#include "oscillators.h"
#include <set>


class LFO {
    public:
        LFO(WaveTable *waveTable);
        double getPos();
        void advance();
        void setFreq(double freq);
        void setWaveform(waveformType waveform);
    private:
        Oscillator oscillator;
        double position;
};

#endif
