#ifndef CHORUS_H
#define CHORUS_H

#include <queue>
#include "soundprocessor.h"
#include <pthread.h>


struct voice {
	int phase;
	double period;
	double cursor;
	double lastSample;
	std::queue<double> alreadyRead;
	std::queue<double> *toRead;
};

class Chorus : public SoundProcessor {
	public:
		Chorus(SoundProcessor *input, double period, double depth);
		double getSample();
		void setDepth(double depth);
		void setPeriod(double period);
	private:
		double getVoiceSample(struct voice &voice);
		struct voice voiceOne;
		struct voice voiceTwo;
   		pthread_mutex_t mutexsum;
		int period;
		double depth;
		SoundProcessor *input;
};

#endif
