#include "square.h"
#include <math.h>

Square::Square(double freq, double level) : Note(freq, level) {}
Square::Square() : Note() {}

double Square::getMySample() {
	return ((phase() > (period / 2)) ? 1 : -1);
}

Note *Square::clone(double freq) {
	return new Square(freq, level);
}
