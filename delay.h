#ifndef DELAY_H
#define DELAY_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

#include <vector>
#include "note.h"

using namespace std;

class Delay {
	public:
		Delay(double periodSeconds, Note *prototype);
		double getSample();
		void addNote(double freq);
		void setTranspose(int transpose);
		void setPrototype(Note *prototype);
	private:
		Note *prototype;
		double getNotesSample();
		void playNote(double freq);
		vector<double> freqs;
		vector<Note*> notes;
		int period;
		int phase;
		int transpose;
};

#endif
