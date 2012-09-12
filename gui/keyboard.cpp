#include "keyboard.h"
#include <math.h>
#include <stdio.h>

using namespace std;


Keyboard::Keyboard() {
	currentSound = &sawtooth;
	octave = 0; 
	transpose = 0;
	attackTime = 0;
	decayTime = 0;
	sustainLevel = 1;
	releaseTime = 0;
	level = 0.1;
	initMaps();
}

void Keyboard::initMaps() {
	freqs[a] = 440;
	freqs[aSharp] = 469.66667;
	freqs[b] = 490;
	freqs[c] = 522.5;
	freqs[cSharp] = 550;
	freqs[d] = 583.33333;
	freqs[dSharp] = 625.77778;
	freqs[e] = 660;
	freqs[f] = 691.42857;
	freqs[fSharp] = 736.66667;
	freqs[g] = 782.22222;
	freqs[gSharp] = 825;
	freqs[a2] = 880;
	freqs[aSharp2] = 938.66667;
	freqs[b2] = 980;
}

void Keyboard::playNote(enum note n) {
	Note *note = currentSound->clone(freqs[n]*pow(2.0, ((double)transpose)/12));
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

void Keyboard::setTriangle() {
	currentSound = &triangle;
}

void Keyboard::setSawtooth() {
	currentSound = &sawtooth;
}

void Keyboard::setSquare() {
	currentSound = &square;
}

void Keyboard::setSine() {
	currentSound = &sine;
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

double Keyboard::adsFactor(int samplesElapsed) {
	if (samplesElapsed < (attackTime * SAMPLE_RATE))
		return (samplesElapsed) / (attackTime * SAMPLE_RATE);
	if (samplesElapsed < ((decayTime+attackTime) * SAMPLE_RATE))
		return 1 - (((samplesElapsed-(attackTime*SAMPLE_RATE)) / (decayTime * SAMPLE_RATE)) * (1-sustainLevel));
	return sustainLevel;
}

double Keyboard::adsrFactor(Note *note) {
	double factor, samplesElapsed, releaseSample, releaseLevel;
	samplesElapsed = note->getSamplesElapsed();
	if(note->isReleased()) {
		releaseSample = note->getReleaseSample();
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
