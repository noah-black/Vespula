#include "envelopebox.h"

EnvelopeBox::EnvelopeBox(Envelope *envelope, QWidget *parent) : 
 QGroupBox(parent),
 envelope(envelope),
 envelopeLabel(this),
 attackSelect(this),
 attackLabel(this),
 decaySelect(this),
 decayLabel(this),
 sustainSelect(this),
 sustainLabel(this),
 releaseSelect(this),
 releaseLabel(this)
{
    envelopeLabel.setText("Envelope");

	attackSelect.setRange(0, 100);
    attackLabel.setText("A");

	decaySelect.setRange(0, 100);
    decayLabel.setText("D");

	sustainSelect.setRange(0, 100);
	sustainSelect.setValue(100);
    sustainLabel.setText("S");

	releaseSelect.setRange(0, 100);
    releaseLabel.setText("R");

	envLayout.addWidget(&envelopeLabel, 0, 0, 1, -1);
	envLayout.addWidget(&attackSelect, 1, 0);
	envLayout.addWidget(&attackLabel, 2, 0, 1, 1, Qt::AlignHCenter);
	envLayout.addWidget(&decaySelect, 1, 1);
	envLayout.addWidget(&decayLabel, 2, 1, 1, 1, Qt::AlignHCenter);
	envLayout.addWidget(&sustainSelect, 1, 2);
	envLayout.addWidget(&sustainLabel, 2, 2, 1, 1, Qt::AlignHCenter);
	envLayout.addWidget(&releaseSelect, 1, 3);
	envLayout.addWidget(&releaseLabel, 2, 3, 1, 1, Qt::AlignHCenter);
    this->setLayout(&envLayout);

	QObject::connect(&attackSelect, SIGNAL(valueChanged(int)), this, SLOT(setAttack(int)));
	QObject::connect(&attackSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&decaySelect, SIGNAL(valueChanged(int)), this, SLOT(setDecay(int)));
	QObject::connect(&decaySelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&sustainSelect, SIGNAL(valueChanged(int)), this, SLOT(setSustain(int)));
	QObject::connect(&sustainSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&releaseSelect, SIGNAL(valueChanged(int)), this, SLOT(setRelease(int)));
	QObject::connect(&releaseSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));
}
void EnvelopeBox::setAttack(int value) {
	envelope->setAttack(((double)value)/50);
}
void EnvelopeBox::setDecay(int value) {
	envelope->setDecay(((double)value)/50);
}
void EnvelopeBox::setSustain(int value) {
	envelope->setSustain(((double)value)/100);
}
void EnvelopeBox::setRelease(int value) {
	envelope->setRelease(((double)value)/50);
}
