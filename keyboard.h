#ifndef MIXER_H
#define MIXER_H 
#include <QObject>
#include <vector>
#include <map>
#include <math.h>
#include <stdio.h>
#include "triangle.h"
#include "sawtooth.h"
#include "square.h"
#include "sine.h"
#include "fm.h"
#include "soundprocessor.h"

using namespace std;

class Keyboard : public SoundProcessor {
	public:
		Keyboard();
		virtual double getSample();
		virtual void playNote(enum note n);
		virtual void releaseNote(enum note n);
		void setOctave(int i);
		void setTransposeInKey(int i);
		void setTranspose(int i);
		void setAttack(double i);
		void setDecay(double i);
		void setSustain(double i);
		void setRelease(double i);
		void setWaveform(int i);
		void setLevel(double i);
		void setFmDepth(double i);
		vector<Note*> getWaveforms();
	protected:
		double adsrFactor(Note *note);
		Note *currentSound;
		map<enum note, double> freqs;
		bool isNote(char c);
		enum note getTransposition(enum note n, int transposeInKey);
		enum note getTransposition(enum note n);
		void initMaps();
		double adsFactor(int samplesElapsed);
		bool isNatural(enum note n);
		bool isSharp(enum note n);
		enum note getNatural(int n);
		enum note getSharp(int n);
		int getInterval(enum note);

		vector<Note*> notes;
		vector<Note*> waveforms;
		map<enum note, Note*> lastNoteFor;
		int octave;
		int transpose;
		int transposeInKey;

		double level;
		double attackTime;
		double decayTime;
		double sustainLevel;
		double releaseTime;
};

#endif
