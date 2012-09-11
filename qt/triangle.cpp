#include "triangle.h"
#include <math.h>

Triangle::Triangle(double freq, double level) : Note(freq, level) {}
Triangle::Triangle() : Note() {}

double Triangle::getMySample() {
	return (fabs(((phase()*4)/period) - 2) - 1);
}

Note *Triangle::clone(double freq) {
	return new Triangle(freq, level);
}
