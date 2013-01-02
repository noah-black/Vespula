#ifndef ENVELOPE_BOX_H
#define ENVELOPE_BOX_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QObject>
#include <string>
#include "envelope.h"

using namespace std;

class EnvelopeBox : public QGroupBox {
    Q_OBJECT
	public:
        EnvelopeBox(Envelope *envelope, QWidget *parent);
    public slots:
		void setAttack(int value);
		void setDecay(int value);
		void setSustain(int value);
		void setRelease(int value);
	private:
        Envelope *envelope;
        QGridLayout envLayout;
		QLabel envelopeLabel;
		QSlider attackSelect;
		QLabel attackLabel;
		QSlider decaySelect;
		QLabel decayLabel;
		QSlider sustainSelect;
		QLabel sustainLabel;
		QSlider releaseSelect;
		QLabel releaseLabel;
};
#endif
