#ifndef MIXER_H
#define MIXER_H 
#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

#include <QObject>
#include <vector>
#include <map>
#include "triangle.h"
#include "sawtooth.h"
#include "square.h"
#include "sine.h"

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

class Keyboard {
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
