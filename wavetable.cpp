#include "wavetable.h"
#include <stdio.h>
#include "soundprocessor.h"

using namespace std;

WaveTable::WaveTable() {
    buildSawtooth();
    buildSquare();
    buildTriangle();
}

WaveTable::~WaveTable() {
    int i;
//    for(i = 0; i < NUM_NOTES; i++) {
//        delete[] triangleTable[i];
//        delete[] sawtoothTable[i];
//        delete[] squareTable[i];
//    }
//    delete[] triangleTable;
//    delete[] sawtoothTable;
//    delete[] squareTable;
}

double WaveTable::triangle(double phase, double freq) {
    return getSample(phase, freq, triangleTable);
} 
double WaveTable::square(double phase, double freq) {
    return getSample(phase, freq, squareTable);
}

double WaveTable::sawtooth(double phase, double freq) {
    return getSample(phase, freq, sawtoothTable);
}

double WaveTable::getSample(double phase, double freq, double **table) {
    double index, closestFreq, ratio, sample, cursor, period, amountRead, amountLeft;
    int closest;
    sample = 0;
    index = 12*(log(freq/440)/log(2))+MIDDLE_A_INDEX;
    closest = (int)floor(index+0.5);
    closest = closest >= NUM_NOTES ? NUM_NOTES - 1 : (closest < 0 ? 0 : closest);
    closestFreq = 440 * pow(2,(double(closest-MIDDLE_A_INDEX))/12);
    period = SAMPLE_RATE/closestFreq;
    ratio = freq/closestFreq;
    amountRead = 0;
    cursor = ratio*phase;
    //printf("index: %f, closest: %d, cursor: %f, period: %f, closestFreq: %f, freq: %f\n", index, closest, cursor, period, closestFreq, freq);
    while(amountRead < ratio) {
        double weightLeft, weightRight;
        int indexLeft, indexRight;
        if(ratio - amountRead >= 1) { // can read whole sample
            if(fmod(cursor, period)+1 < period) { // no period wrapping stuff to worry about
                if(fmod(cursor, period) == 0) {
                    weightLeft = 0;
                    indexLeft = 0;
                    weightRight = 1;
                    indexRight = (int)floor(fmod(cursor,period));
                }
                else {
                    weightLeft = 1-fmod(fmod(cursor, period), 1);
                    indexLeft = (int)floor(fmod(cursor,period));
                    weightRight = fmod(fmod(cursor, period), 1);
                    indexRight = (int)ceil(fmod(cursor,period));
                }
            }
            else {
                weightLeft = fmod(period, 1)-fmod(fmod(cursor, period), 1);
                indexLeft = (int)floor(period);
                weightRight = fmod(fmod(cursor+1,period), 1);
                indexRight = 0;
            }
            amountRead += 1;
            cursor += 1;
        }
        else {
            amountLeft = ratio - amountRead;
            if(fmod(cursor, period)+amountLeft < period) { // no period wrapping stuff to worry about
                if(fmod(fmod(cursor, period), 1) + amountLeft < 1) { // we only worry about one sample 
                    weightLeft = 0;
                    indexLeft = 0;
                    weightRight = amountLeft;
                    indexRight = (int)floor(fmod(cursor,period));
                }
                else {
                    weightLeft = 1-fmod(fmod(cursor, period), 1);
                    indexLeft = (int)floor(fmod(cursor,period));
                    weightRight = amountLeft - weightLeft;
                    indexRight = (int)fmod(cursor+1, period);
                }
            }
            else {
                weightLeft = fmod(period, 1)-fmod(fmod(cursor, period), 1);
                indexLeft = (int)floor(period);
                weightRight = fmod(fmod(cursor+amountLeft, period), 1);
                indexRight = 0;
            }
            amountRead = ratio;
        }
        sample += weightLeft*table[closest][indexLeft] + weightRight*table[closest][indexRight];
    }
    return sample/ratio;
}

double WaveTable::sine(double phase, double freq) {
    return sin(((phase*freq)/SAMPLE_RATE)*2*PI);
}

void WaveTable::buildTriangle() {
    int i, j;   
    double freq, period;
    for(i = 0; i < NUM_NOTES; i++) {
        freq = 440 * pow(2,(double(i-MIDDLE_A_INDEX))/12); // sawtoothTable[MIDDLE_A_INDEX] = A440
        period = SAMPLE_RATE/freq;
        triangleTable[i] = new double[(int)ceil(period)];
        for(j = 0; j < ceil(period); j++) {
            triangleTable[i][j] = triangleFunction(j, freq);
        }
    }
}

void WaveTable::buildSquare() {
    int i, j;   
    double freq, period;
    for(i = 0; i < NUM_NOTES; i++) {
        freq = 440 * pow(2,(double(i-MIDDLE_A_INDEX))/12); // sawtoothTable[MIDDLE_A_INDEX] = A440
        period = SAMPLE_RATE/freq;
        squareTable[i] = new double[(int)ceil(period)];
        for(j = 0; j < ceil(period); j++) {
            squareTable[i][j] = squareFunction(j, freq);
        }
    }
}

void WaveTable::buildSawtooth() {
    int i, j;   
    double freq, period;
    for(i = 0; i < NUM_NOTES; i++) {
        freq = 440 * pow(2,(double(i-MIDDLE_A_INDEX))/12); // sawtoothTable[MIDDLE_A_INDEX] = A440
        period = SAMPLE_RATE/freq;
        sawtoothTable[i] = new double[(int)ceil(period)];
        for(j = 0; j < ceil(period); j++) {
            sawtoothTable[i][j] = sawtoothFunction(j, freq);
        }
    }
}

double WaveTable::sawtoothFunction(double phase, double f) {
    double t, sum, sample;
    int i;
    t = phase/SAMPLE_RATE;
    sum = 0;
    for(i = 1; i < SAMPLE_RATE/(2*f); i++) {
        sum += (i%2==1?1:-1)*sin(2*PI*i*f*t)/i;
    }
    sample = (2*sum)/PI;
    return sample;
}

double WaveTable::squareFunction(double phase, double f) {
    double t, sum, sample;
    int i;
    t = phase/SAMPLE_RATE;
    sum = 0;
    for(i = 1; i < (SAMPLE_RATE/2)/f; i+=2) {
        sum += (i%2==1?1:-1) * sin(2*PI*i*f*t)/i;
    }
    sample = (2*sum)/PI;
    return sample;
}

double WaveTable::triangleFunction(double phase, double f) {
    double t, sum, sample;
    int i;
    t = phase/SAMPLE_RATE;
    sum = 0;
    for(i = 1; i < (SAMPLE_RATE/2)/f; i+=2) {
        sum += (i%2==1?1:-1) * sin(2*PI*i*f*t)/i;
    }
    sample = (2*sum)/PI;
    return sample;
}
