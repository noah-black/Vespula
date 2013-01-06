#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#include "soundprocessor.h"

using namespace std;

class Oscillators {
	public:
        static double triangle(double phase, double period);
        static double sawtooth(double phase, double period);
        static double square(double phase, double period);
        static double sine(double phase, double period);
};
#endif
