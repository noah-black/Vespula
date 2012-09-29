#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "note.h"

class Sawtooth : public Note {
	public:
		Sawtooth(double, enum note);
		Sawtooth();
		double getMySample();
		Note *clone(double freq, enum note);
		string getName();
	protected:
		static const double antiAlias = 0.99;
};

#endif
