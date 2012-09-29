#ifndef SINE_H
#define SINE_H

#include "note.h"

class Sine: public Note {
	public:
		Sine(double, enum note);
		Sine();
		double getMySample();
		Note *clone(double freq, enum note);
		string getName();
};
#endif
