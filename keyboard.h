#ifndef MIXER_H
#define MIXER_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

#include "soundmodule.h"
#include "note.h"
#include <vector>
#include <map>

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
		void takeInput(char c);
		double getSample();
	private:
		void playNote(char c);
		bool isNote(char c);
		void initMaps();

		vector<Note*> notes;
		vector<SoundModule*> modules;
		map<enum note, double> freqs;
		map<char, enum note> keyMap;
		int octave;
};

#endif
