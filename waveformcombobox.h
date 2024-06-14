#ifndef WAVEFORMCOMBOBOX_H
#define WAVEFORMCOMBOBOX_H

#include <QComboBox>
#include <QObject>
#include <QPointer>
#include "wavetable.h"
#include "soundprocessor.h"

class WaveformComboBox : public QComboBox {
    Q_OBJECT
    public:
        WaveformComboBox(QWidget *parent);
	virtual ~WaveformComboBox() override {}; // Ensure virtual destructor
        waveformType getWaveformType(int i);
};

#endif
