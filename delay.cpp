#include "delay.h"
#include <algorithm>
#include <stdio.h>

Delay::Delay(double feedback, double periodSeconds, double dry) : loop(periodSeconds*SAMPLE_RATE) {
	this->feedback = feedback;
	this->dry = dry;
	period = periodSeconds*SAMPLE_RATE;
	phase = 0;
}

double Delay::getSample(double premixedSample) {
	double oldSample, newSample;
	phase = phase % period;
	oldSample = loop[phase] * feedback;
	if (oldSample < ((0.001)*CEILING))
		oldSample = 0;
	newSample = ((dry*premixedSample)+((1.0-dry)*oldSample));
	loop[phase] = premixedSample + oldSample;
	phase++;
	return newSample;
}
