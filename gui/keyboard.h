#ifndef MIXER_H
#define MIXER_H 
#include <QObject>
#include <vector>
#include <map>
#include "triangle.h"
#include "sawtooth.h"
#include "square.h"
#include "sine.h"
#include "soundprocessor.h"

using namespace std;

enum note {
	a,
	aSharp, b,
	c,
	cSharp,
	d,
	dSharp,
	e,
	f,
	fSharp,
	g,
	gSharp,
	a2,
	aSharp2,
	b2
};

class Keyboard : public SoundProcessor {
	public:
		Keyboard();
		virtual double getSample();
		virtual void playNote(enum note n);
		virtual void releaseNote(enum note n);
		void setOctave(int i);
		void setTranspose(int i);
		void setAttack(double i);
		void setDecay(double i);
		void setSustain(double i);
		void setRelease(double i);
		void setWaveform(int i);
		vector<Note*> getWaveforms();
	protected:
		double adsrFactor(Note *note);
		Note *currentSound;
		map<enum note, double> freqs;
		bool isNote(char c);
		void initMaps();
		double adsFactor(int samplesElapsed);

		vector<Note*> notes;
		vector<Note*> waveforms;
		map<enum note, Note*> lastNoteFor;
		int octave;
		int transpose;

		double level;
		double attackTime;
		double decayTime;
		double sustainLevel;
		double releaseTime;
};

#endif
