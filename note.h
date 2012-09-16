#ifndef NOTE_H
#define NOTE_H

#include "soundprocessor.h"
#include <string>

using namespace std;

enum note_state {
	held,
	released
};

class Note {
	public:
		Note(double freq = 440, double level = 0.1);
		void release();
		bool isReleased();
		int getSamplesElapsed();
		int getReleaseSample();
		void setFreq(double freq);
		void setReleaseSample(int);
		void setLevel(double level);
		void incrementLevel(double amount);
		bool isDead(double);
		double getFreq();

		double getSample();
		virtual double getMySample() = 0;
		virtual Note *clone(double freq) = 0;
		virtual string getName() = 0;
	protected:
		void advance();
		double phase();
		enum note_state state;
		double period;
		int samplesElapsed;
		int releaseSample;
		double freq;
		double level;
};
#endif
