#include "delay.h"
#include "sawtooth.h"
#include <algorithm>
#include <stdio.h>
#include <math.h>

Delay::Delay(double periodSeconds, Note *prototype): freqs(periodSeconds*SAMPLE_RATE, 0) {
	this->prototype = prototype;
	period = periodSeconds*SAMPLE_RATE;
	phase = 0;
	transpose = 0;
}

void Delay::setPrototype(Note *prototype) {
	this->prototype = prototype;
}

double Delay::getSample() {
	double sample;
	sample = getNotesSample();
	if(freqs[phase] != 0)
		playNote(freqs[phase]);
	phase++;
	phase = phase % period;
	return sample;
}

double Delay::getNotesSample() {
	double sample = 0;
	vector<Note*>::iterator it;
	it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample();
		if((*it)->isDead())
			it = notes.erase(it);
		else
			it++;
	}
	return sample;
}

void Delay::playNote(double freq) {
	notes.push_back(prototype->clone(freq*pow(2.0, ((double)transpose)/12)));
}

void Delay::addNote(double freq) {
	freqs[phase] = freq;
}

void Delay::setTranspose(int transpose) {
	this->transpose = transpose;
}
