#include "vibrato.h"
#include <math.h>
#include <stdio.h>

Vibrato::Vibrato(SoundProcessor *input, double period, double depth) {
	this->depth = depth;
	this->input = input;
	this->period = (int)(period * SAMPLE_RATE);
	cursor = 0;
	phase = 0;
	lastSample = 0;
	sampleGitCount = 0;
}

double Vibrato::getSample() {
	double virtSampleSize, sample, offset, amountToRead;
	double i;
	sample = 0;
	virtSampleSize = 1 + ((depth * sin(2*PI*(((double)phase)/period))) / SAMPLE_RATE);
	for(i = 0; i < virtSampleSize;){
		offset = fmod(cursor, 1);
		if(offset == 0) { 
			lastSample = input->getSample();
			sampleGitCount++;
		}
		amountToRead = (virtSampleSize-i > 1-offset) ? 1-offset : virtSampleSize-i;
		i += amountToRead;
		cursor += amountToRead;
		sample += (amountToRead/virtSampleSize) * lastSample;
	}
	phase++;
	if(phase >= period && cursor >= period) {
		sampleGitCount = 0;
		phase -= period;
		cursor -= period;
	}
	return sample;
}
