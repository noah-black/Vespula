#include "note.h"

using namespace std;

Note::Note(double freq, enum note baseNote) {
	this->freq = freq;
	this->baseNote = baseNote;
	state = held;
	period = SAMPLE_RATE/freq;
	samplesElapsed = 0;
	releaseSample = -1;
}

void Note::setFreq(double freq) {
	this->freq = freq;
	period = SAMPLE_RATE/freq;
}

int Note::getSamplesElapsed() {
	return samplesElapsed;
}

double Note::getFreq() {
	return freq;
}

enum note Note::getNote() {
	return baseNote;
}

void Note::setNote(enum note baseNote) {
	this->baseNote = baseNote;
}

int Note::getReleaseSample() {
	return releaseSample;
}

void Note::setReleaseSample(int releaseSample) {
	this->releaseSample = releaseSample;
}

void Note::release() {
	if (this->isReleased()) 
		return;
	state = released;
	releaseSample = samplesElapsed;

}

bool Note::isReleased() {
	return state == released;
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
	return getMySample();
}
