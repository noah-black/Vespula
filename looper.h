#ifndef LOOPER_H
#define LOOPER_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

#include <vector>
#include "note.h"
#include "keyboard.h"
#include <pthread.h>

using namespace std;

struct savedNote {
	enum note note;
	int octave;
	int duration;
};

class Looper : public Keyboard {
	public:
		Looper(NoteFactory *noteFactory, double periodSeconds);
		double getSample();
		void releaseNote(enum note n);
        void setDuration(double value);
        void clear();
	private:
   		pthread_mutex_t mutexsum;
   		pthread_mutex_t savedNoteMutex;
		void playSavedNote(struct savedNote);
		double getNotesSample();
		vector< vector<struct savedNote> > savedNotes;
		int period;
		int phase;
};

#endif
