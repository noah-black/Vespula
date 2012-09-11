#include "note.h"

using namespace std;

Note::Note(double freq, double level) {
	this->freq = freq;
	this->level = level;
	state = held;
	period = SAMPLE_RATE/freq;
	samplesElapsed = 0;
}

void Note::setFreq(double freq) {
	this->freq = freq;
}

void Note::setLevel(double level) {
	this->level = level;
}

int Note::getSamplesElapsed() {
	return samplesElapsed;
}

int Note::getReleaseSample() {
	return releaseSample;
}

void Note::release() {
	state = released;
	releaseSample = samplesElapsed;
}

bool Note::isReleased() {
	return state == released;
}

void Note::incrementLevel(double amount) {
	level += amount;
	if(level > 1)
		level = 1;
	else if(level < 0)
		level = 0;
}

bool Note::isDead(double releaseTime) {
	if(state != released)
		return false;
	else
		return ((samplesElapsed - releaseSample) > (releaseTime * SAMPLE_RATE));
}

void Note::advance() {
	samplesElapsed++;
}

double Note::phase() {
	return fmod(samplesElapsed, period);
}

double Note::getSample() {
	advance();
	return getMySample() * CEILING * level;
}
