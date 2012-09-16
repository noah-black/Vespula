#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "note.h"

class Triangle: public Note {
	public:
		Triangle(double, double);
		Triangle();
		double getMySample();
		Note *clone(double freq);
		string getName();
};
#endif
