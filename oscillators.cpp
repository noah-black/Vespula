#include "oscillators.h"

using namespace std;

double Oscillators::triangle(waveformPrecision phase, waveformPrecision period) {
	return (fabs(((phase*4)/period) - 2.0) - 1.0);
}

double Oscillators::sawtooth(waveformPrecision phase, waveformPrecision period) {
    //return ((phase/(period)) * 2) - 1;
	return (phase < period*0.99) ? (((phase/(period*0.99)) * 2) - 1) : ((((phase - (period*0.99))/(period*(0.01))) * -2) + 1);
}

double Oscillators::square(waveformPrecision phase, waveformPrecision period) {
	return ((phase > (period / 2)) ? 1 : -1);
}

double Oscillators::sine(waveformPrecision phase, waveformPrecision period) {
	return sin((phase/period)*2*PI);
}
