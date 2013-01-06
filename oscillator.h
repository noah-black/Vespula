#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "soundprocessor.h"
#include "envelope.h"
#include "wavetable.h"
#include <string>

using namespace std;

class Oscillator {
	public:
        Oscillator(WaveTable *waveTable, waveformType *waveform, double freq);
        void setFreq(double freq);
        virtual double getSample();
    protected:
        WaveTable *waveTable;
        void advance();
        double phase;
        double period;
        pthread_mutex_t setFreqMutex;
        waveformType *waveform;
};
#endif
