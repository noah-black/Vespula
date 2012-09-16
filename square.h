#ifndef SQUARE_H 
#define SQUARE_H 

#include "note.h"

class Square: public Note {
	public:
		Square(double freq, double level);
		Square();
		double getMySample();
		Note *clone(double freq);
		string getName();
};
#endif
