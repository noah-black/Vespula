#ifndef FM_H
#define FM_H

#include "oscillator.h"
#include "envelopable.h"
#include "envelopeconnection.h"
#include <vector>

using namespace std;

class FM : public Oscillator, public Envelopable {
	public:
		FM(waveformType* waveform, double freq, double *depth);
		virtual double getSample();
		void setDepth(double i);
        void envelopeUpdate(double amount);
	private:
		double *depth;
		double carrierPhase;
        double envelopeModifier;
};

#endif
