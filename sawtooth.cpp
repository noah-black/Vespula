#include "sawtooth.h"

Sawtooth::Sawtooth(double freq, enum note baseNote) : Note(freq, baseNote) {
}

Sawtooth::Sawtooth() : Note() { 
}

double Sawtooth::getMySample() {
	return (phase() < period*antiAlias) ? (((phase()/(period*antiAlias)) * 2) - 1) : ((((phase() - (period*antiAlias))/(period*(1-antiAlias))) * -2) + 1);
}

Note *Sawtooth::clone(double newfreq, enum note baseNote) {
	return new Sawtooth(newfreq, baseNote);
}

string Sawtooth::getName() {
	return "Sawtooth";
}
