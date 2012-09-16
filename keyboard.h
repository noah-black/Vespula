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
	n1,
	s1,
	n2,
	s2,
	n3,
	n4,
	s4,
	n5,
	s5,
	n6,
	s6,
	n7,
	n8,
	s8,
	n9,
	s9,
	n10,
	n11,
	s11,
	n12,
	s12,
	n13,
	s13,
	n14,
	n15,
	s15,
	n16,
	s16
};

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
		vector<Note*> getWaveforms();
	protected:
		double adsrFactor(Note *note);
		Note *currentSound;
		map<enum note, double> freqs;
		bool isNote(char c);
		void initMaps();
		double adsFactor(int samplesElapsed);
		enum note getTransposition(enum note);
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
