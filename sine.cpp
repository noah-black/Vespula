#include "sine.h"


Sine::Sine(double freq, enum note baseNote) : Note(freq, baseNote) {}
Sine::Sine() : Note() { }

double Sine::getMySample() {
	return sin((phase()/period)*2*PI);
}

Note *Sine::clone(double freq, enum note baseNote) {
	return new Sine(freq, baseNote);
}

string Sine::getName() {
	return "Sine";
}
