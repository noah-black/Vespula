#include "chorus.h"
#include <math.h>
#include <stdio.h>

Chorus::Chorus(SoundProcessor *input, double period, double depth) {
	this->depth = depth;
	this->input = input;
	this->period = (int)(period * SAMPLE_RATE);

	voiceOne.period = this->period;
	voiceOne.phase = 0;
	voiceOne.cursor = 0;
	voiceOne.lastSample = 0;
	voiceOne.toRead = &(voiceTwo.alreadyRead);

	voiceTwo.period = this->period*1.1;
	voiceTwo.phase = 0;
	voiceTwo.cursor = 0;
	voiceTwo.lastSample = 0;
	voiceTwo.toRead = &(voiceOne.alreadyRead);

	pthread_mutex_init(&mutexsum, NULL);
}

double Chorus::getSample() {
	double sample = 0;
	sample += getVoiceSample(voiceOne);
	sample += getVoiceSample(voiceTwo);
	return sample/2;
}

double Chorus::getVoiceSample(struct voice &voice) {
	double virtSampleSize, sample, offset, amountToRead;
	double i;
	pthread_mutex_lock (&mutexsum);
	sample = 0;
	virtSampleSize = 1 + ((depth * sin(2*PI*(((double)voice.phase)/voice.period))) / SAMPLE_RATE);
	for(i = 0; i < virtSampleSize;){
		offset = fmod(voice.cursor, 1);
		if(offset == 0) { 
			if((voice.toRead)->empty()) {
				voice.lastSample = input->getSample();
				voice.alreadyRead.push(voice.lastSample);
			}
			else {
				voice.lastSample = (voice.toRead)->front();
				(voice.toRead)->pop();
			}
		}
		amountToRead = (virtSampleSize-i > 1-offset) ? 1-offset : virtSampleSize-i;
		i += amountToRead;
		voice.cursor += amountToRead;
		sample += (amountToRead/virtSampleSize) * voice.lastSample;
	}
	pthread_mutex_unlock (&mutexsum);
	voice.phase++;
	if(voice.phase >= voice.period && voice.cursor >= voice.period) {
		voice.phase -= voice.period;
		voice.cursor -= voice.period;
	}
	return sample;
}

void Chorus::setDepth(double depth) {
	pthread_mutex_lock (&mutexsum);
	this->depth = depth;
	pthread_mutex_unlock (&mutexsum);
}

void Chorus::setPeriod(double period) {
	pthread_mutex_lock (&mutexsum);
	this->period = (int)(period * SAMPLE_RATE);
	pthread_mutex_unlock (&mutexsum);
}
