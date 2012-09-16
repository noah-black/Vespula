#ifndef SP_H
#define SP_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0
#define PI		3.14159265358979323846

#include <math.h>

class SoundProcessor {
	public:
		virtual double getSample() = 0;
};

#endif
