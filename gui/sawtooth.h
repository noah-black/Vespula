#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "note.h"

class Sawtooth : public Note {
	public:
		Sawtooth(double freq, double level);
		Sawtooth();
		double getMySample();
		Note *clone(double freq);
		string getName();
};

#endif
