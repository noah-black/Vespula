#ifndef LFO_BOX_H
#define LFO_BOX_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QObject>
#include <string>
#include "lfo.h"
#include "waveformcombobox.h"

using namespace std;

class LfoBox : public QGroupBox {
    Q_OBJECT
	public:
        LfoBox(LFO *lfo, QWidget *parent);
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
