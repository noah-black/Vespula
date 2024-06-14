#include "looper.h"
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
	pthread_mutex_lock(&noteMutex);
	pthread_mutex_lock(&mutexsum);
	if(!savedNotes[phase].empty()) {
		for(std::vector<struct savedNote>::iterator it = savedNotes[phase].begin(); it != savedNotes[phase].end(); ++it)
			playSavedNote(*it);
	}
	phase++;
	phase = phase % period;
	pthread_mutex_unlock(&mutexsum);
	pthread_mutex_unlock(&noteMutex);
	return sample;
}

double Looper::getNotesSample() {
	double sample = 0;
	std::deque<Note*>::iterator it;
	pthread_mutex_lock(&noteMutex);
	pthread_mutex_lock(&lastNoteMutex);
    it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample();
		if((*it)->isDead()) {
            enum note n;
            n = (*it)->getNote();
            if(lastNoteFor.find(n) != lastNoteFor.end() && (lastNoteFor[n] == (*it))){
                releaseNoteInternal(n);
            }
            delete (*it);
			it = notes.erase(it);
		}
		else
			it++;
	}
	pthread_mutex_unlock(&lastNoteMutex);
	pthread_mutex_unlock(&noteMutex);
	return sample;
}

void Looper::releaseNote(enum note n) {
	pthread_mutex_lock(&noteMutex);
	pthread_mutex_lock(&lastNoteMutex);
	pthread_mutex_lock(&mutexsum);
    releaseNoteInternal(n);
    pthread_mutex_unlock(&mutexsum);
	pthread_mutex_unlock(&lastNoteMutex);
	pthread_mutex_unlock(&noteMutex);
}

void Looper::releaseNoteInternal(enum note n) {
	if(lastNoteFor.find(n) != lastNoteFor.end()) {
		Note *note = lastNoteFor[n];
		struct savedNote sNote;
		sNote.note = n;
		sNote.duration = note->getSamplesElapsed();
		sNote.octave = octave;
		savedNotes[(phase-sNote.duration)%period < 0 ? (phase-sNote.duration)%period + period : (phase-sNote.duration)%period].push_back(sNote);
		note->release();
        lastNoteFor.erase(n);
	}
}

void Looper::playSavedNote(struct savedNote sNote) {
    Note *note;
    double freq;
	freq = freqs[getTransposition(sNote.note)]*pow(2.0, sNote.octave + ((double)transpose)/12);
    note = noteFactory->getNote(freq, sNote.note);
	note->setReleaseSample(sNote.duration);
	notes.push_back(note);
    cullNotes();
}

void Looper::setDuration(double value) {
	pthread_mutex_lock(&mutexsum);
    period = value*SAMPLE_RATE;
    phase = phase >= period ? 0 : phase;
    savedNotes.resize(period);
	pthread_mutex_unlock(&mutexsum);
}

void Looper::clear() {
    pthread_mutex_lock(&noteMutex);
    pthread_mutex_lock(&mutexsum);
    for(std::vector< std::vector<struct savedNote> >::iterator it = savedNotes.begin(); it != savedNotes.end(); ++it)
        it->clear();
    std::deque<Note*>::iterator it;
    it = notes.begin();
    while(it != notes.end()) {
        delete (*it);
        it = notes.erase(it);
    }
    pthread_mutex_unlock(&mutexsum);
    pthread_mutex_unlock(&noteMutex);
}
