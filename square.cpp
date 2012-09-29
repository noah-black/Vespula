#include "square.h"
#include <math.h>

Square::Square(double freq, enum note baseNote) : Note(freq, baseNote) {}
Square::Square() : Note() {}

double Square::getMySample() {
	return ((phase() > (period / 2)) ? 1 : -1);
}

Note *Square::clone(double freq, enum note baseNote) {
	return new Square(freq, baseNote);
}

string Square::getName() {
	return "Square";
}
