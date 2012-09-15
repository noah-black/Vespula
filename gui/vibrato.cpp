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
	pthread_mutex_init(&mutexsum, NULL);
}

double Vibrato::getSample() {
	double virtSampleSize, sample, offset, amountToRead;
	double i;
	pthread_mutex_lock (&mutexsum);
	sample = 0;
	virtSampleSize = 1 + ((depth * sin(2*PI*(((double)phase)/period))) / SAMPLE_RATE);
	for(i = 0; i < virtSampleSize;){
		offset = fmod(cursor, 1);
		if(offset == 0) { 
			lastSample = input->getSample();
		}
		amountToRead = (virtSampleSize-i > 1-offset) ? 1-offset : virtSampleSize-i;
		i += amountToRead;
		cursor += amountToRead;
		sample += (amountToRead/virtSampleSize) * lastSample;
	}
	phase++;
	if(phase >= period && cursor >= period) {
		phase -= period;
		cursor -= period;
	}
	pthread_mutex_unlock (&mutexsum);
	return sample;
}

void Vibrato::setDepth(double depth) {
	pthread_mutex_lock (&mutexsum);
	this->depth = depth;
	pthread_mutex_unlock (&mutexsum);
}

void Vibrato::setPeriod(double period) {
	pthread_mutex_lock (&mutexsum);
//	phase = 0;
//	cursor = 0;
	this->period = (int)(period * SAMPLE_RATE);
	pthread_mutex_unlock (&mutexsum);
}
