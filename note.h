#ifndef NOTE_H
#define NOTE_H

#include "soundprocessor.h"
#include "envelope.h"
#include "oscillator.h"
#include "envelopeconnection.h"
#include <string>
#include <vector>

using namespace std;

enum note_state {
	held,
	released
};

class Note : public SoundProcessor {
	public:
		Note(Oscillator *oscillator, Envelope *envelope, double freq = 440, enum note baseNote = n1);
        ~Note();
		virtual void release();
		bool isReleased();
		int getSamplesElapsed();
		int getReleaseSample();
		virtual void setFreq(double freq);
		void setReleaseSample(int);
		void incrementLevel(double amount);
		bool isDead();
		double getFreq();
		enum note getNote();
		void setNote(enum note);
		double getSample();
        void addEnvelopeConnection(EnvelopeConnection *envelopeConnection);
	protected:
        vector<EnvelopeConnection*> envelopeConnections;
		void advance();
		enum note baseNote;
		enum note_state state;
		double period;
		int samplesElapsed;
		int releaseSample;
		double freq;
        Oscillator *oscillator;
        Envelope *envelope;
};
#endif
