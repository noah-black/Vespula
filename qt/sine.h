#ifndef SINE_H
#define SINE_H

#include "note.h"

class Sine: public Note {
	public:
		Sine(double, double);
		Sine();
		double getMySample();
		Note *clone(double freq);
};
#endif
