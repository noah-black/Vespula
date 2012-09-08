#ifndef SAWTOOTH_H
#define SAWTOOTH_H

#include "note.h"

class Sawtooth : public Note {
	public:
		Sawtooth(double freq, double release, double level);
		double getSample();
		bool isDead();
	protected:
		double freq;
		double period;
		double level;
		double samples_elapsed;
		double decay;
		double attack;
		double delay;
		double sustain;
		double release;
};
#endif
