#include "sine.h"


Sine::Sine(double freq, double level) : Note(freq, level) { }
Sine::Sine() : Note() { }

double Sine::getMySample() {
	return sin((phase()/period)*2*PI);
}

Note *Sine::clone(double freq) {
	return new Sine(freq, level);
}

string Sine::getName() {
	return "Sine";
}
