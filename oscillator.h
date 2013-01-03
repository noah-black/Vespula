#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "soundprocessor.h"
#include "envelope.h"
#include <string>

using namespace std;

class Oscillator {
	public:
        Oscillator(waveformType *waveform, double freq);
        ~Oscillator();
        void setFreq(double freq);
        virtual double getSample();
    protected:
        void advance();
        void initialize();
        double calculateSample();
        double phase;
        double period;
        double *samples;
        bool uninitialized;
        waveformType *waveform;
};
#endif
