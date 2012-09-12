#include "sawtooth.h"
#include <math.h>

Sawtooth::Sawtooth(double freq, double release, double level) {
	this->freq = freq;
	this->release = release;
	this->level = level;
	period = SAMPLE_RATE/freq;
	samples_elapsed = 0;
}

double Sawtooth::getSample() {
	double release_factor, phase;
	release_factor = 1 - (samples_elapsed) / (release * SAMPLE_RATE);
	if (release_factor < 0)
		release_factor = 0;
	phase = fmod(samples_elapsed, period);
	samples_elapsed++;
//	return (((phase/period) * 2) - 1) * CEILING * level * release_factor;
	return (((phase/period) * 2) - 1) * CEILING * level;
}

bool Sawtooth::isDead() {
	return (samples_elapsed > (release * SAMPLE_RATE));
}

Note *Sawtooth::clone(double newfreq) {
	return new Sawtooth(newfreq, release, level);
}
