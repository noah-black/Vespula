#include "lfobox.h"
#include <cmath>
#include <cstdio>

LfoBox::LfoBox(LFO *lfo, QWidget *parent)
    : QGroupBox(parent), lfo(lfo), lfoLabel("LFO", this),
      freqSelect(Qt::Horizontal, this), freqLabel("Freq", this),
      waveformSelect(this), waveformLabel("Waveform", this) {
  // Set up frequency slider
  freqSelect.setRange(1, 100);
  freqSelect.setValue(13);

  // Set up layout
  layout.addWidget(&lfoLabel, 0, 0, 1, -1);
  layout.addWidget(&freqSelect, 1, 0, 2, 1);
  layout.addWidget(&freqLabel, 4, 0, 1, 1, Qt::AlignHCenter);
  layout.addWidget(&waveformSelect, 1, 1, 1, 1, Qt::AlignHCenter);
  layout.addWidget(&waveformLabel, 2, 1, 1, 1, Qt::AlignHCenter);
  this->setLayout(&layout);

  // Connect signals and slots
  connect(&freqSelect, &QSlider::valueChanged, this, &LfoBox::setFreq);
  connect(&freqSelect, &QSlider::valueChanged, this,
          [this]() { this->setFocus(); });

  connect(&waveformSelect, QOverload<int>::of(&QComboBox::activated), this,
          &LfoBox::changeWaveform);
  connect(&waveformSelect, QOverload<int>::of(&QComboBox::activated), this,
          [this]() { this->setFocus(); });
}

void LfoBox::setFreq(int value) {
  lfo->setFreq(std::pow(static_cast<double>(value) / 100.0, 2) * 30);
}

void LfoBox::changeWaveform(int i) {
  lfo->setWaveform(waveformSelect.getWaveformType(i));
}

LfoBox::~LfoBox() {
  // Destructor code here if needed
}
