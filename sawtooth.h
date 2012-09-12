#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "note.h"

class Sawtooth : public Note {
	public:
		Sawtooth(double freq, double release, double level);
		double getSample();
		Note *clone(double freq);
		bool isDead();
};
#endif
