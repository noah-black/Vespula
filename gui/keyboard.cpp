#include "keyboard.h"
#include <math.h>
#include <stdio.h>

using namespace std;


Keyboard::Keyboard() {
	octave = 0; 
	transpose = 0;
	attackTime = 0;
	decayTime = 0;
	sustainLevel = 1;
	releaseTime = 0;
	level = 0.1; 
	waveforms.push_back(new Sawtooth());
	waveforms.push_back(new Triangle());
	waveforms.push_back(new Square());
	waveforms.push_back(new Sine());
	currentSound = waveforms[0];
	initMaps();
}

void Keyboard::initMaps() {
	for(int i = 0; i <= (int)b2; i++)
		freqs[(enum note)i] = 440*pow(2.0, ((double)i/12));
}

void Keyboard::playNote(enum note n) {
	if(lastNoteFor.find(n) != lastNoteFor.end() && !lastNoteFor[n]->isReleased())
		lastNoteFor[n]->release();
	Note *note = currentSound->clone(freqs[n]*pow(2.0, octave+((double)transpose)/12));
	lastNoteFor[n] = note;
	notes.push_back(note);
}

void Keyboard::releaseNote(enum note n) {
	if(lastNoteFor.find(n) != lastNoteFor.end())
		lastNoteFor[n]->release();
}

double Keyboard::getSample() {
	double sample = 0;
	vector<Note*>::iterator it;
	it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample() * adsrFactor(*it);
		if((*it)->isDead(releaseTime))
			it = notes.erase(it);
		else
			it++;
	}
	return sample;
}

void Keyboard::setOctave(int i) {
	octave = i;
}

void Keyboard::setTranspose(int i) {
	transpose = i;
}

void Keyboard::setAttack(double i) {
	attackTime = i;
}

void Keyboard::setDecay(double i) {
	decayTime = i;
}

void Keyboard::setSustain(double i) {
	sustainLevel = i;
}

void Keyboard::setRelease(double i) {
	releaseTime = i;
}

void Keyboard::setWaveform(int i) {
	currentSound = waveforms[i];
}

double Keyboard::adsFactor(int samplesElapsed) {
	if (samplesElapsed < (attackTime * SAMPLE_RATE))
		return (samplesElapsed) / (attackTime * SAMPLE_RATE);
	if (samplesElapsed < ((decayTime+attackTime) * SAMPLE_RATE))
		return 1 - (((samplesElapsed-(attackTime*SAMPLE_RATE)) / (decayTime * SAMPLE_RATE)) * (1-sustainLevel));
	return sustainLevel;
}

double Keyboard::adsrFactor(Note *note) {
	double factor, releaseLevel;
	int samplesElapsed, releaseSample;
	samplesElapsed = note->getSamplesElapsed();
	if(note->isReleased()) {
		releaseSample = note->getReleaseSample();
		if((samplesElapsed - releaseSample) >= (releaseTime*SAMPLE_RATE))
			return 0;
		releaseLevel = adsFactor(releaseSample);
		factor = releaseLevel * (1 - (samplesElapsed - releaseSample) / (releaseTime * SAMPLE_RATE));
		if (factor < 0)
			factor = 0;
		if (factor > 1)
			factor = 1;
		return factor;
	}
	return adsFactor(samplesElapsed);
}

vector<Note*> Keyboard::getWaveforms() {
	return waveforms;
}
