#include "lpf.h"
#include <math.h>
#include <stdio.h>

LPF::LPF(SoundProcessor *input) {
	this->input = input;
	pthread_mutex_init(&mutexsum, NULL);
	alpha = 0.05;
	started = false;
}

double LPF::getSample() {
	double outputSample, nextSample;
	nextSample = input->getSample();
	if(nextSample != nextSample)
		printf("NAN\n");
	if (!started) {
		started = true;
		lastOutputSample = nextSample;
		return nextSample;
	}
	outputSample = lastOutputSample + (alpha * (nextSample - lastOutputSample));
	lastOutputSample = outputSample;
	return outputSample*8;
}
