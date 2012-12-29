#ifndef SE_H
#define SE_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0
#define PI		3.14159265358979323846

#include <math.h>

class SoundEffect {
	public:
		virtual double getSample(double input) = 0;
};

#endif
