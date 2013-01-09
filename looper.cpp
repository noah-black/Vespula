#include "looper.h"
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <iostream>

Looper::Looper(NoteFactory *noteFactory, double periodSeconds): Keyboard(noteFactory), savedNotes(periodSeconds*SAMPLE_RATE) {
	period = periodSeconds*SAMPLE_RATE;
	phase = 0;
	pthread_mutex_init(&mutexsum, NULL);
}

double Looper::getSample() {
	double sample;
	sample = getNotesSample();
	pthread_mutex_lock(&mutexsum);
	if(!savedNotes[phase].empty()) {
		for(vector<struct savedNote>::iterator it = savedNotes[phase].begin(); it != savedNotes[phase].end(); ++it)
			playSavedNote(*it);
	}
	phase++;
	phase = phase % period;
	pthread_mutex_unlock(&mutexsum);
	return sample;
}

double Looper::getNotesSample() {
	double sample = 0;
	vector<Note*>::iterator it;
	pthread_mutex_lock(&noteMutex);
    it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample();
		if(!((*it)->isReleased()) && ((*it)->getReleaseSample() == (*it)->getSamplesElapsed())) {
			(*it)->release();
		}
		if((*it)->isDead()) {
            pthread_mutex_lock(&lastNoteMutex);
            delete (*it);
			it = notes.erase(it);
            pthread_mutex_unlock(&lastNoteMutex);
		}
		else
			it++;
	}
	pthread_mutex_unlock(&noteMutex);
	it = notes.begin();
	return sample;
}

void Looper::releaseNote(enum note n) {
	pthread_mutex_lock(&lastNoteMutex);
	if(lastNoteFor.find(n) != lastNoteFor.end()) {
		Note *note = lastNoteFor[n];
		struct savedNote sNote;
		sNote.note = n;
		sNote.duration = note->getSamplesElapsed();
		sNote.octave = octave;
	    pthread_mutex_lock(&mutexsum);
		savedNotes[(phase-sNote.duration)%period < 0 ? (phase-sNote.duration)%period + period : (phase-sNote.duration)%period].push_back(sNote);
	    pthread_mutex_unlock(&mutexsum);
		note->release();
        lastNoteFor.erase(n);
	}
	pthread_mutex_unlock(&lastNoteMutex);
}

void Looper::playSavedNote(struct savedNote sNote) {
    Note *note;
    double freq;
	freq = freqs[getTransposition(sNote.note)]*pow(2.0, sNote.octave + ((double)transpose)/12);
    note = noteFactory->getNote(freq, sNote.note);
	note->setReleaseSample(sNote.duration);
	pthread_mutex_lock(&noteMutex);
	notes.push_back(note);
	pthread_mutex_unlock(&noteMutex);
}

void Looper::setDuration(double value) {
	pthread_mutex_lock(&mutexsum);
    period = value*SAMPLE_RATE;
    phase = phase >= period ? 0 : phase;
    savedNotes.resize(period);
	pthread_mutex_unlock(&mutexsum);
}

void Looper::clear() {
	pthread_mutex_lock(&mutexsum);
	pthread_mutex_lock(&noteMutex);
	for(vector< vector<struct savedNote> >::iterator it = savedNotes.begin(); it != savedNotes.end(); ++it)
        it->clear();
	vector<Note*>::iterator it;
    notes.clear();
	pthread_mutex_unlock(&noteMutex);
	pthread_mutex_unlock(&mutexsum);
}
