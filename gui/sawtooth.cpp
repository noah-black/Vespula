#include "sawtooth.h"

Sawtooth::Sawtooth(double freq, double level) : Note(freq, level) {} 
Sawtooth::Sawtooth() : Note() {} 

double Sawtooth::getMySample() {
	return (((phase()/period) * 2) - 1);
}

Note *Sawtooth::clone(double newfreq) {
	return new Sawtooth(newfreq, level);
}

string Sawtooth::getName() {
	return "Sawtooth";
}
