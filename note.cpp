#include "note.h"
#include <stdio.h>

using namespace std;

Note::Note(Oscillator *oscillator, Envelope *envelope, double freq, enum note baseNote) : envelope(envelope) {
    this->oscillator = oscillator;
	this->freq = freq;
	this->baseNote = baseNote;
	state = held;
	period = SAMPLE_RATE/freq;
	samplesElapsed = 0;
	releaseSample = -1;
}

Note::~Note() {
    delete oscillator;
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

bool Note::isDead() {
	if(state != released)
		return false;
	else 
        return envelope->isDead(samplesElapsed, releaseSample);
}

void Note::advance() {
    vector<EnvelopeConnection*>::const_iterator iter;
    for (iter=envelopeConnections.begin(); iter != envelopeConnections.end(); ++iter) {
        isReleased() ? (*iter)->notify(samplesElapsed, releaseSample) : (*iter)->notify(samplesElapsed);
    }
    samplesElapsed++;
}

double Note::getSample() {
    double levelEnvelope, sample;
    levelEnvelope = isReleased() ? envelope->getFactor(samplesElapsed, releaseSample) : envelope->getFactor(samplesElapsed);
	sample = oscillator->getSample()*levelEnvelope;
	advance();
    return sample;
}

void Note::addEnvelopeConnection(EnvelopeConnection *envelopeConnection) {
    envelopeConnections.push_back(envelopeConnection);
}
