#include "filter.h"
#include <stdio.h>

Filter::Filter()
{
    pthread_mutex_init(&myMutex, NULL);
    cutoff = 1;
    resonance = 0;
    ql = 1;
    qp = 5;
    updateCoef();
    o2=0; 
    o1=0; 
    i2=0; 
    i1=0;
    o2p=0; 
    o1p=0; 
    i2p=0; 
    i1p=0;
}

double Filter::getSample(double input) {
    double outputl, outputp;
    updateCoef();
    pthread_mutex_lock(&myMutex);

    outputl = b0*input + b1*i1 + b0*i2 - a1*o1 - a2*o2;

    o2=o1; 
    o1=outputl; 
    i2=i1; 
    i1=input;

    outputp = b0p*input - b0p*i2p - a1p*o1p - a2p*o2p;

    o2p=o1p; 
    o1p=outputp; 
    i2p=i1p; 
    i1p=input;

    pthread_mutex_unlock(&myMutex);
    return outputl+(outputp);
}

void Filter::setCutoff(double cutoff) {
    this->cutoff = cutoff;
    updateCoef();
}

double Filter::getCutoffHz(double cutoff) {
    return (SAMPLE_RATE/500) + ((SAMPLE_RATE/2) - (SAMPLE_RATE/100))*pow(cutoff, 2);
}

void Filter::setResonance(double resonance) {
    this->resonance = resonance*10;
    updateCoef();
}

void Filter::updateCoef() {
    double omega, sn, cs, alphal, alphap, cutoffPos;
    pthread_mutex_lock(&myMutex);
    cutoffPos = getCutoff();
    omega = (PI*2.0*(getCutoffHz(cutoffPos)))/SAMPLE_RATE;
    sn = sin(omega); 
    cs = cos(omega);
    alphal = sn/(2.0*ql);
    alphap = sn/(2.0*qp);

    a0 = 1.0/(1.0+alphal);
    a1 = (-2.0*cs)*a0;
    a2 = (1.0-alphal)*a0;
    b1 = (1.0-cs)*a0;
    b0 = b1 * 0.5;

    a0p = 1.0 / ( 1.0 + alphap );
    a1p = ( -2.0 * cs ) * a0p;
    a2p = ( 1.0 - alphap ) * a0p;
    b0p = alphap * a0p * getResonance();

    pthread_mutex_unlock(&myMutex);
}

double Filter::getCutoff() {
    double cutoffPos;
    cutoffPos = cutoff+getLfoPosition(); 
    cutoffPos = cutoffPos > 1 ? 1 : cutoffPos < 0 ? 0 : cutoffPos;
    return cutoffPos;
}

double Filter::getResonance() {
    return resonance;
}
