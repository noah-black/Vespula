#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "soundprocessor.h"
#include "envelope.h"
#include <string>

using namespace std;

class Oscillator {
	public:
        Oscillator(waveformType *waveform, double freq);
        void setFreq(double freq);
        virtual double getSample();
    protected:
        void advance();
        double phase;
        double period;
        waveformType *waveform;
};
#endif
