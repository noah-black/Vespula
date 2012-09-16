#ifndef VIBRATO_H
#define VIBRATO_H

#include <vector>
#include "soundprocessor.h"
#include <pthread.h>

using namespace std;

class Vibrato : public SoundProcessor {
	public:
		Vibrato(SoundProcessor *input, double period, double depth);
		double getSample();
		void setDepth(double depth);
		void setPeriod(double period);
	private:
		double cursor;
		int phase;
   		pthread_mutex_t mutexsum;
		int period;
		double depth;
		double lastSample;
		SoundProcessor *input;
};

#endif
