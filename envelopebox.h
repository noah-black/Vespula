#ifndef ENVELOPE_BOX_H
#define ENVELOPE_BOX_H

#include <QGroupBox>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QObject>
#include <string>
#include "keyboard.h"

using namespace std;

class EnvelopeBox : public QGroupBox {
    Q_OBJECT
	public:
        EnvelopeBox(Keyboard **keyboard, QWidget *parent);
    public slots:
		void setAttack(int value);
		void setDecay(int value);
		void setSustain(int value);
		void setRelease(int value);
	private:
        Keyboard **keyboard;
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
