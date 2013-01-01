#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#include "soundprocessor.h"

using namespace std;

class Oscillators {
	public:
        static double triangle(waveformPrecision phase, waveformPrecision period);
        static double sawtooth(waveformPrecision phase, waveformPrecision period);
        static double square(waveformPrecision phase, waveformPrecision period);
        static double sine(waveformPrecision phase, waveformPrecision period);
};
#endif
