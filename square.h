#ifndef SQUARE_H 
#define SQUARE_H 

#include "note.h"

class Square: public Note {
	public:
		Square(double freq, enum note);
		Square();
		double getMySample();
		Note *clone(double freq, enum note);
		string getName();
};
#endif
