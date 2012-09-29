#include "triangle.h"
#include <math.h>

Triangle::Triangle(double freq, enum note baseNote) : Note(freq, baseNote) {}
Triangle::Triangle() : Note() {}

double Triangle::getMySample() {
	return (fabs(((phase()*4)/period) - 2) - 1);
}

Note *Triangle::clone(double freq, enum note baseNote) {
	return new Triangle(freq, baseNote);
}

string Triangle::getName() {
	return "Triangle";
}
