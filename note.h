#ifndef NOTE_H
#define NOTE_H

#include "soundprocessor.h"
#include <string>

using namespace std;

enum note_state {
	held,
	released
};

class Note : public SoundProcessor {
	public:
		Note(double freq = 440, enum note baseNote = n1);
		virtual void release();
		bool isReleased();
		int getSamplesElapsed();
		int getReleaseSample();
		virtual void setFreq(double freq);
		void setReleaseSample(int);
		void incrementLevel(double amount);
		bool isDead(double);
		double getFreq();
		enum note getNote();
		void setNote(enum note);
		double getSample();

		virtual double getMySample() = 0;
		virtual Note *clone(double freq, enum note) = 0;
		virtual string getName() = 0;
	protected:
		void advance();
		double phase();
		enum note baseNote;
		enum note_state state;
		double period;
		int samplesElapsed;
		int releaseSample;
		double freq;
};
#endif
