#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "soundeffect.h"

using namespace std;

class Envelope {
	public:
        Envelope(double attack, double decay, double sustain, double release);
		void setAttack(int value);
		void setDecay(int value);
		void setSustain(int value);
		void setRelease(int value);
        double getFactor();
        double adsFactor();
        void setReleased();
    private:
        double attack;
        double decay;
        double sustain;
        double release;
        int samplesElapsed;
        int releaseSample;
        bool isReleased;
};
#endif
