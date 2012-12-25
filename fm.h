#include "note.h"

class FM : public Note {
	public:
		FM(Note *input, double freq, double *depth);
		~FM();
		double getMySample();
		void setDepth(double i);
		void setFreq(double freq);
		Note *clone(double freq, enum note);
		string getName();
	private:
		Note *input;
		double *depth;
		double carrierPhase;
};
