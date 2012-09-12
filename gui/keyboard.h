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
	aSharp,
	b,
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
		double getSample();
		void playNote(enum note n);
		void releaseNote(enum note n);
		void setTriangle();
		void setSawtooth();
		void setSquare();
		void setSine();
		void setTranspose(int i);
		void setAttack(double i);
		void setDecay(double i);
		void setSustain(double i);
		void setRelease(double i);
	private:
		bool isNote(char c);
		void initMaps();
		double adsrFactor(Note *note);
		double adsFactor(int samplesElapsed);

		vector<Note*> notes;
		map<enum note, double> freqs;
		map<enum note, Note*> lastNoteFor;
		Note *currentSound;
		Triangle triangle;
		Sawtooth sawtooth;
		Square square;
		Sine sine;

		int octave;
		int transpose;

		double level;
		double attackTime;
		double decayTime;
		double sustainLevel;
		double releaseTime;
};

#endif
