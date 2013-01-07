#include "lfobox.h"
#include <stdio.h>

LfoBox::LfoBox(LFO *lfo, QWidget *parent) :
    QGroupBox(parent),
    lfo(lfo),
    lfoLabel(this),
    freqSelect(this),
    freqLabel(this),
    waveformSelect(this),
    waveformLabel(this)
{
    lfoLabel.setText("LFO");

    freqSelect.setRange(1, 100);
    freqLabel.setText("Freq");
    freqSelect.setValue(13);

    waveformLabel.setText("Waveform");

    layout.addWidget(&lfoLabel, 0, 0, 1, -1);
    layout.addWidget(&freqSelect, 1, 0, 2, 1);
    layout.addWidget(&freqLabel, 4, 0, 1, 1, Qt::AlignHCenter);
    layout.addWidget(&waveformSelect, 1, 1, 1, 1, Qt::AlignHCenter);
    layout.addWidget(&waveformLabel, 2, 1, 1, 1, Qt::AlignHCenter);
    this->setLayout(&layout);

    QObject::connect(&freqSelect, SIGNAL(valueChanged(int)), this, SLOT(setFreq(int)));
    QObject::connect(&freqSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&waveformSelect, SIGNAL(activated(int)), this, SLOT(changeWaveform(int)));
    QObject::connect(&waveformSelect, SIGNAL(activated(int)), this, SLOT(setFocus()));
}

void LfoBox::setFreq(int value) {
    printf("%f\n", pow((double)value/100, 2)*30);
    lfo->setFreq(pow((double)value/100, 2)*30);
}

void LfoBox::changeWaveform(int i) {
    lfo->setWaveform(waveformSelect.getWaveformType(i));
}
