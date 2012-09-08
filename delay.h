#ifndef DELAY_H
#define DELAY_H

#define SAMPLE_RATE 44100.0
#define CEILING 32767.0

#include "soundmodule.h"
#include <vector>

using namespace std;

class Delay : public SoundModule {
	public:
		Delay(double feedback, double periodSeconds, double dry);
		double getSample(double sample);
	private:
	 	vector<double> loop;
		double feedback;
		int period;
		double dry;
		int phase;
};

#endif
