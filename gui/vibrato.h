#ifndef VIBRATO_H
#define VIBRATO_H

#include <vector>
#include "soundprocessor.h"

using namespace std;

class Vibrato : SoundProcessor {
	public:
		Vibrato(SoundProcessor *input, double period, double depth);
		double getSample();
	private:
		double cursor;
		int phase;
		int period;
		int sampleGitCount;
		double depth;
		double lastSample;
		SoundProcessor *input;
};

#endif
