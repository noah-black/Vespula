#ifndef LFO_BOX_H
#define LFO_BOX_H

#include "lfo.h"
#include "waveformcombobox.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QWidget>
#include <string>

class LfoBox : public QGroupBox {
  Q_OBJECT
public:
  LfoBox(LFO *lfo, QWidget *parent);
  virtual ~LfoBox();

public slots:
  void setFreq(int value);
  void changeWaveform(int i);

private:
  LFO *lfo;
  QGridLayout layout;
  QLabel lfoLabel;
  QSlider freqSelect;
  QLabel freqLabel;
  WaveformComboBox waveformSelect;
  QLabel waveformLabel;
};
#endif
