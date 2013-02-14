#include "filter.h"
#include <stdio.h>

Filter::Filter(SoundProcessor *proc) : 
    in(WINDOW_SIZE, 0), 
    out(WINDOW_SIZE, 0), 
    proc(proc)
{
    f = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*((WINDOW_SIZE/2)+1));
    toF = fftw_plan_dft_r2c_1d(WINDOW_SIZE, &in[0], f, 0);
    toT = fftw_plan_dft_c2r_1d(WINDOW_SIZE, f, &out[0], 0);
    width = 3000;
    cutoff = (SAMPLE_RATE/2)-width;
    resonance = 0;
    bin_size = SAMPLE_RATE / (2*WINDOW_SIZE);
    pthread_mutex_init(&myMutex, NULL);
}

double Filter::getSample() {
    double sample = proc->getSample();
    for(int i = 0; i < WINDOW_SIZE-1; i++)
        swap(i, i+1);
    in[WINDOW_SIZE-1] = sample;
    prepare();
    fftw_execute(toF);
    pthread_mutex_lock(&myMutex);
    for(int i = 0; i < (WINDOW_SIZE/2)+1; i++) {
        double factor, freq;
        freq = (i+1)*bin_size;
        if(freq >= cutoff+width)
            factor = 0;
        else if(freq > cutoff)
            factor = pow(cos(((freq-cutoff)/width)*PI/2), 2);
        else if(freq > cutoff-width)
            factor = 1+(resonance * pow(sin(((freq-(cutoff-width))/width)*PI), 2));
        else
            factor = 1;

        f[0][i] *= factor;
        f[1][i] *= factor;
        //printf("%f %f\n", freq, factor);
    }
    pthread_mutex_unlock(&myMutex);
    fftw_execute(toT);
    recover();
    return out[WINDOW_SIZE/2]/WINDOW_SIZE;
}

Filter::~Filter() {
    fftw_destroy_plan(toF);
    fftw_destroy_plan(toT);
    free(f);
}

void Filter::prepare() {
    for(int i = 0; i < WINDOW_SIZE; i++)
        in[i] = in[i] * (0.5 * (1 - cos(2*PI*i/(double)WINDOW_SIZE)));
}

void Filter::recover() {
    for(int i = 0; i < WINDOW_SIZE; i++) {
        in[i] = in[i] / (0.5 * (1 - cos(2*PI*i/(double)WINDOW_SIZE)));
    }
}

void Filter::swap(int i, int j) {
    int temp;
    temp = in[i];
    in[i] = in[j];
    in[j] = temp;
}

void Filter::setCutoff(double cutoff) {
    pthread_mutex_lock(&myMutex);
    this->cutoff = (cutoff*cutoff*(SAMPLE_RATE)/2)-width;
    pthread_mutex_unlock(&myMutex);
}

void Filter::setResonance(double resonance) {
    pthread_mutex_lock(&myMutex);
    this->resonance = resonance*5;
    pthread_mutex_unlock(&myMutex);
}
