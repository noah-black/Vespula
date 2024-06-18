#ifndef WAVEFORMCOMBOBOX_H
#define WAVEFORMCOMBOBOX_H

#include "soundprocessor.h"
#include "wavetable.h"
#include <QComboBox>
#include <QObject>
#include <QPointer>

class WaveformComboBox : public QComboBox {
  Q_OBJECT
public:
  WaveformComboBox(QWidget *parent);
  virtual ~WaveformComboBox() override {}; // Ensure virtual destructor
  waveformType getWaveformType(int i);
};

#endif
