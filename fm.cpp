#include "fm.h"
#include <stdio.h>

FM::FM(Note *input, double freq, double *depth) : Note(freq, input->getNote()) {
	this->input = input;
	this->freq = freq;
	this->depth = depth;
	carrierPhase = 0;
}

FM::~FM() {
	delete input;
}

double FM::getMySample() {
	double in, out;
	in = input->getSample();
	out = sin(2*PI*(carrierPhase/period));
	carrierPhase = fmod((carrierPhase+1+(((*depth)*in)/freq)), period);
	return out;
}

string FM::getName() {
	return input->getName();
}


Note *FM::clone(double freq, enum note n) {
	return new FM(input->clone(freq, n), freq, depth);
}

void FM::setFreq(double freq) {
	Note::setFreq(freq);
	input->setFreq(freq);
}

