#include "note.h"
#include <stdio.h>


Note::Note(Oscillator *oscillator, Envelope *envelope, double freq, enum note baseNote, double velocity) : envelope(envelope) {
    this->oscillator = oscillator;
	this->freq = freq;
	this->baseNote = baseNote;
	this->velocity = velocity;
	state = held;
	period = SAMPLE_RATE/freq;
	samplesElapsed = 0;
	releaseSample = -1;
    killCounter = 0;
    killed = false;
}

Note::~Note() {
    delete oscillator;
    std::vector<EnvelopeConnection*>::iterator it;
    for(it = envelopeConnections.begin(); it != envelopeConnections.end(); ++it)
        delete (*it);
    std::vector<SoundEffect*>::iterator eit;
    for(eit = noteEffects.begin(); eit != noteEffects.end(); ++eit)
        delete (*eit);
}

void Note::setFreq(double freq) {
	this->freq = freq;
	period = SAMPLE_RATE/freq;
	oscillator->setFreq(freq);
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
	if(state == released)
		return;
    state = released;
	releaseSample = samplesElapsed;
}

bool Note::isReleased() {
	return state == released;
}

bool Note::isDead() {
	if(killed && killCounter > killTime) {
        return true;
    }
	if(state != released)
		return false;
    return envelope->isDead(samplesElapsed, releaseSample);
}

void Note::advance() {
    std::vector<EnvelopeConnection*>::const_iterator iter;
    for (iter=envelopeConnections.begin(); iter != envelopeConnections.end(); ++iter) {
        isReleased() ? (*iter)->notify(samplesElapsed, releaseSample, velocity) : (*iter)->notify(samplesElapsed, velocity);
    }
    samplesElapsed++;
    if(state != released && releaseSample > -1 && samplesElapsed > releaseSample){
        state = released;
    }
}

double Note::getSample() {
    double levelEnvelope, sample;
    levelEnvelope = (state == released) ? envelope->getFactor(samplesElapsed, releaseSample) : envelope->getFactor(samplesElapsed);
    sample = oscillator->getSample()*levelEnvelope*velocity;
    if(killed) {
        sample = killTime == 0 ? 0 : sample*((double)(killTime-killCounter)/(double)killTime);
        killCounter++;
    }
    for(std::vector<SoundEffect*>::iterator it = noteEffects.begin(); it != noteEffects.end(); ++it) {
        sample = (*it)->getSample(sample);
    }
    advance();
    return sample;
}

void Note::addEnvelopeConnection(EnvelopeConnection *envelopeConnection) {
    envelopeConnections.push_back(envelopeConnection);
}

Oscillator *Note::getOscillator() {
    return oscillator;
}

void Note::kill(int killTime) {
    this->killTime = killTime;
    killed = true;
}

bool Note::isKilled() {
    return killed;
}

void Note::setWaveform(waveformType waveform) {
    oscillator->setWaveform(waveform);
}

void Note::addNoteEffect(SoundEffect *effect) {
    noteEffects.push_back(effect);
}
