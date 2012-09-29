#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "note.h"

class Triangle: public Note {
	public:
		Triangle(double, enum note);
		Triangle();
		double getMySample();
		Note *clone(double freq, enum note);
		string getName();
};
#endif
