#ifndef MIXER_H
#define MIXER_H 
#include <QObject>
#include <vector>
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
		virtual double getSample();
		virtual void playNote(enum note n);
		virtual void releaseNote(enum note n);
		void setOctave(int i);
		void setTransposeInKey(int i);
		void setTranspose(int i);
	protected:
		map<enum note, double> freqs;
		bool isNote(char c);
		void releaseNoteInternal(enum note n);
		enum note getTransposition(enum note n, int transposeInKey);
		enum note getTransposition(enum note n);
		void initMaps();
		bool isNatural(enum note n);
		bool isSharp(enum note n);
		enum note getNatural(int n);
		enum note getSharp(int n);
        pthread_mutex_t noteMutex;
        pthread_mutex_t lastNoteMutex;
		int getInterval(enum note);
        NoteFactory *noteFactory;

		vector<Note*> notes;
		map<enum note, Note*> lastNoteFor;

		int octave;
		int transpose;
		int transposeInKey;
};

#endif
