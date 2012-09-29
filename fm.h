#include "note.h"

class FM : public Note {
	public:
		FM(Note *input, double freq = 440, double depth = 0);
		~FM();
		double getMySample();
		double setDepth(double i);
		void setFreq(double freq);
		Note *clone(double freq, enum note);
		string getName();
	private:
		Note *input;
		double depth;
		double carrierPhase;
};
