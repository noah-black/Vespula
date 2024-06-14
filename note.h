#ifndef NOTE_H
#define NOTE_H

#include "soundprocessor.h"
#include "soundeffect.h"
#include "envelope.h"
#include "oscillator.h"
#include "envelopeconnection.h"
#include <string>
#include <vector>


enum note_state {
	held,
    released
};

class Note : public SoundProcessor {
	public:
		Note(Oscillator *oscillator, Envelope *envelope, double freq = 440, enum note baseNote = n1, double velocity = 1);
        ~Note();
		virtual void release();
		bool isReleased();
		int getSamplesElapsed();
		int getReleaseSample();
		virtual void setFreq(double freq);
		void setWaveform(waveformType waveform);
		void setReleaseSample(int);
		void incrementLevel(double amount);
		bool isDead();
		bool isKilled();
		double getFreq();
		enum note getNote();
		void setNote(enum note);
		virtual double getSample();
        void addEnvelopeConnection(EnvelopeConnection *envelopeConnection);
        Oscillator *getOscillator();
        void kill(int killTime);
        void addNoteEffect(SoundEffect *effect);
	protected:
        std::vector<EnvelopeConnection*> envelopeConnections;
        std::vector<SoundEffect*> noteEffects;
		virtual void advance();
		enum note baseNote;
		enum note_state state;
		double period;
		int samplesElapsed;
		int releaseSample;
		double freq;
        double velocity;
        int killCounter;
        int killTime;
        bool killed;
        Oscillator *oscillator;
        Envelope *envelope;
};

#endif
