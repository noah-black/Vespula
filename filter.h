#ifndef FILTER_H
#define FILTER_H

#include <fftw3.h>
#include <soundprocessor.h>
#include <stdlib.h>
#include <pthread.h>


#define WINDOW_SIZE 16

class Filter : public SoundProcessor {
    public:
        Filter(SoundProcessor*);
        ~Filter();
        double getSample();
        void setCutoff(double cutoff);
        void setResonance(double resonance);
	private:
        void prepare();
        void recover();
        void swap(int i, int j);
        fftw_complex *f;
        fftw_plan toF;
        fftw_plan toT;
        vector<double> in;
        vector<double> out;
        SoundProcessor *proc;
        pthread_mutex_t myMutex;
        double cutoff;
        double resonance;
        double width;
        double bin_size;
};

#endif
