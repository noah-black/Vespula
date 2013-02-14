#ifndef MIXER_H
#define MIXER_H 
#include <QObject>
#include <deque>
#include <map>
#include <string>
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include "fm.h"
#include "soundprocessor.h"
#include "oscillators.h"
#include "oscillator.h"
#include "notefactory.h"
#include "note.h"

using namespace std;

class Keyboard : public SoundProcessor {
	public:
		Keyboard(NoteFactory *noteFactory);
		~Keyboard();
		virtual double getSample();
		virtual void playNote(enum note n);
        void playNote(Note *note);
		virtual void releaseNote(enum note n);
		void setOctave(int i);
		void setTransposeInKey(int i);
		void setTranspose(int i);
        void clearAll();
        void setMonophonic(bool monophonic);
		enum note getTransposition(enum note n, int transposeInKey);
		enum note getTransposition(enum note n);
        double getFreq(enum note n, int octave);
        double getFreq(enum note n);
        void cullNotes();
        void setWaveform(waveformType waveform);
	protected:
		map<enum note, double> freqs;
		bool isNote(char c);
		virtual void releaseNoteInternal(enum note n);
		bool isNatural(enum note n);
		bool isSharp(enum note n);
		enum note getNatural(int n);
		enum note getSharp(int n);
		void initMaps();
        pthread_mutex_t noteMutex;
        pthread_mutex_t lastNoteMutex;
		int getInterval(enum note);
        NoteFactory *noteFactory;

		deque<Note*> notes;
		map<enum note, Note*> lastNoteFor;

        unsigned int voices;

		int octave;
		int transpose;
		int transposeInKey;
        bool monophonic;
};

#endif
