#include "looper.h"
#include "sawtooth.h"
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <new>
#include <iostream>

Looper::Looper(double periodSeconds): savedNotes(periodSeconds*SAMPLE_RATE) {
	period = periodSeconds*SAMPLE_RATE;
	phase = 0;
	pthread_mutex_init(&mutexsum, NULL);
}

double Looper::getSample() {
	pthread_mutex_lock (&mutexsum);
	double sample;
	sample = getNotesSample();
	if(!savedNotes[phase].empty()) {
		for(vector<struct savedNote*>::iterator it = savedNotes[phase].begin(); it != savedNotes[phase].end(); ++it)
			playSavedNote(*it);
	}
	phase++;
	phase = phase % period;
	pthread_mutex_unlock (&mutexsum);
	return sample;
}

double Looper::getNotesSample() {
	double sample = 0;
	vector<Note*>::iterator it;
	it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample() * adsrFactor(*it) * level;
		if(!((*it)->isReleased()) && ((*it)->getReleaseSample() == (*it)->getSamplesElapsed())) {
			(*it)->release();
		}
		if((*it)->isDead(releaseTime)) {
			it = notes.erase(it);
		}
		else
			it++;
	}
	return sample;
}

void Looper::releaseNote(enum note n) {
	pthread_mutex_lock (&mutexsum);
	if(lastNoteFor.find(n) != lastNoteFor.end()) {
		Note *note = lastNoteFor[n];
		struct savedNote *sNote;
		try {
			sNote = new struct savedNote;
		}
		catch (bad_alloc& ba) {
			cerr << "bad_alloc caught: " << ba.what() << endl;
		}
		sNote->note = n;
		sNote->duration = note->getSamplesElapsed();
		sNote->octave = octave;
		savedNotes[(phase-sNote->duration)%period < 0 ? (phase-sNote->duration)%period + period : (phase-sNote->duration)%period].push_back(sNote);
		note->release();
	}
	pthread_mutex_unlock (&mutexsum);
}

void Looper::playSavedNote(struct savedNote *sNote) {
	Note *note = currentSound->clone(freqs[getTransposition(sNote->note)]*pow(2.0, sNote->octave + ((double)transpose)/12), sNote->note);
    if(fmEnabled)
        note = new FM(note, freqs[getTransposition(sNote->note)]*pow(2.0, sNote->octave + ((double)transpose)/12), &fmDepth);
	note->setReleaseSample(sNote->duration);
	notes.push_back(note);
}
