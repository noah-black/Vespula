#include "keyboard.h"

using namespace std;

Keyboard::Keyboard() {
	octave = 0; 
	transpose = 0;
	transposeInKey = 0;
	attackTime = 0;
	decayTime = 0;
	sustainLevel = 1;
	releaseTime = 0;
	level = 0.01; 
	waveforms.push_back(new Sawtooth());
	waveforms.push_back(new Triangle());
	waveforms.push_back(new Square());
	waveforms.push_back(new Sine());
	//currentSound = new FM(waveforms[0]);
	currentSound = waveforms[0];
	initMaps();
}

void Keyboard::initMaps() {
	for(int i = 0; i <= (int)s16; i++)
		freqs[(enum note)i] = 440*pow(2.0, ((double)i/12));
}

void Keyboard::setFmDepth(double i) {
	((FM*)currentSound)->setDepth(i);
}

void Keyboard::setLevel(double i) {
	level = i;
}

void Keyboard::playNote(enum note n) {
	if(lastNoteFor.find(n) != lastNoteFor.end() && !lastNoteFor[n]->isReleased())
		lastNoteFor[n]->release();
	Note *note = currentSound->clone(freqs[getTransposition(n)]*pow(2.0, octave+((double)transpose)/12), n);
	lastNoteFor[n] = note;
	notes.push_back(note);
}

void Keyboard::releaseNote(enum note n) {
	if(lastNoteFor.find(n) != lastNoteFor.end())
		lastNoteFor[n]->release();
}

enum note Keyboard::getTransposition(enum note n, int transposeInKey) {
	if(isNatural(n))
		return getNatural(getInterval(n)+transposeInKey);
	else
		return getSharp(getInterval(n)+transposeInKey);
}

enum note Keyboard::getTransposition(enum note n) {
	if(isNatural(n))
		return getNatural(getInterval(n)+transposeInKey);
	else
		return getSharp(getInterval(n)+transposeInKey);
}

bool Keyboard::isNatural(enum note n) {
	return (n == n1 || n == n2 || n == n3 || n == n4 || n == n5 || n == n6 || n == n7 || n == n8 || n == n9 || n == n10 || n == n11 || n == n12 || n == n13 || n == n14 || n == n15 || n == n16);
}

bool Keyboard::isSharp(enum note n) {
	return (n == s1 || n == s2 || n == s4 || n == s5 || n == s6 || n == s8 || n == s9 || n == s11 || n == s12 || n == s13 || n == s15 || n == s16);
}

enum note Keyboard::getNatural(int n) {
	switch (n) {
		case 1: return n1;
		case 2: return n2;
		case 3: return n3;
		case 4: return n4;
		case 5: return n5;
		case 6: return n6;
		case 7: return n7;
		case 8: return n8;
		case 9: return n9;
		case 10: return n10;
		case 11: return n11;
		case 12: return n12;
		case 13: return n13;
		case 14: return n14;
		case 15: return n15;
		case 16: return n16;
	}
	return n1;
}


enum note Keyboard::getSharp(int n) {
	switch (n) {
		case 1: return s1;
		case 2: return s2;
		case 3: return n4;
		case 4: return s4;
		case 5: return s5;
		case 6: return s6;
		case 7: return n8;
		case 8: return s8;
		case 9: return s9;
		case 10: return n11;
		case 11: return s11;
		case 12: return s12;
		case 13: return s13;
		case 14: return n15;
		case 15: return s15;
		case 16: return s16;
	}
	return s1;
}

int Keyboard::getInterval(enum note n) {
	switch (n) {
		case n1: return 1;
		case s1: return 1;
		case n2: return 2;
		case s2: return 2;
		case n3: return 3;
		case n4: return 4;
		case s4: return 4;
		case n5: return 5;
		case s5: return 5;
		case n6: return 6;
		case s6: return 6;
		case n7: return 7;
		case n8: return 8;
		case s8: return 8;
		case n9: return 9;
		case s9: return 9;
		case n10: return 10;
		case n11: return 11;
		case s11: return 11;
		case n12: return 12;
		case s12: return 12;
		case n13: return 13;
		case s13: return 13;
		case n14: return 14;
		case n15: return 15;
		case s15: return 15;
		case n16: return 16;
		case s16: return 16;

	}
	return 0;
}


double Keyboard::getSample() {
	double sample = 0;
	vector<Note*>::iterator it;
	it = notes.begin();
	while(it != notes.end()) {
		sample += (*it)->getSample() * adsrFactor(*it) * level;
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

void Keyboard::setTransposeInKey(int i) {
	enum note oldNote, newNote;
	double oldFreq, newFreq;
	int oldTransposeInKey = transposeInKey;
	vector<Note*>::iterator it;
	transposeInKey = i;
	for(it = notes.begin(); it != notes.end(); ++it) {
		oldNote = getTransposition((*it)->getNote(), oldTransposeInKey);
		newNote = getTransposition((*it)->getNote(), transposeInKey);
		oldFreq = (*it)->getFreq();
		newFreq = oldFreq * (freqs[newNote]/freqs[oldNote]);
		(*it)->setFreq(newFreq);
	}
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
