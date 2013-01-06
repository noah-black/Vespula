#ifndef FM_H
#define FM_H

#include "oscillator.h"
#include "modulatable.h"
#include "envelopeconnection.h"
#include "lfoable.h"
#include <vector>

using namespace std;

class FM : public Oscillator, public Modulatable, public Lfoable {
	public:
		FM(WaveTable *waveTable, waveformType* waveform, double freq, double *depth);
		virtual double getSample();
		void setDepth(double i);
        void modulate(double amount);
	private:
		double *depth;
		double carrierPhase;
        double envelopeModifier;
};

#endif
