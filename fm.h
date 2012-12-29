#include "note.h"
#include "envelope.h"

class FM : public Note {
	public:
		FM(Note *input, double freq, double *depth);
		~FM();
		double getMySample();
		void setDepth(double i);
		void setFreq(double freq);
        virtual void release();
		Note *clone(double freq, enum note);
		string getName();
	private:
		Note *input;
		double *depth;
		double carrierPhase;
        Envelope envelope;
};
