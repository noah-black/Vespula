#include "fmbox.h"

FmBox::FmBox(NoteFactory *noteFactory, QWidget *parent) : 
    QGroupBox(parent),
    noteFactory(noteFactory),
    fmLabel(this),
    fmDepthLabel(this),
    fmDepthSelect(this),
    fmEnabled(this),
    fmEnvelopeLabel(this),
    fmEnvAmountSelect(this),
    fmEnvelopeEnabled(this),
    fmLfoLabel(this),
    fmLfoAmountSelect(this),
    fmLfoEnabled(this)
{
    setMinimumHeight(200);
    fmLabel.setText("FM");
    fmDepthLabel.setText("Depth");
    fmEnvelopeLabel.setText("Envelope");
    fmLfoLabel.setText("LFO");

    fmDepthSelect.setRange(0, 100);
    fmEnvAmountSelect.setRange(0, 100);

    fmLayout.addWidget(&fmLabel, 0, 0, 1, -1, Qt::AlignHCenter);

    fmLayout.addWidget(&fmDepthLabel, 1, 0, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmDepthSelect, 2, 0, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmEnabled, 3, 0, 1, 1, Qt::AlignHCenter);

    fmLayout.addWidget(&fmEnvelopeLabel, 1, 1, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmEnvAmountSelect, 2, 1, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmEnvelopeEnabled, 3, 1, 1, 1, Qt::AlignHCenter);

    fmLayout.addWidget(&fmLfoLabel, 1, 2, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmLfoAmountSelect, 2, 2, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmLfoEnabled, 3, 2, 1, 1, Qt::AlignHCenter);

    this->setLayout(&fmLayout);

    QObject::connect(&fmDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFmDepth(int)));
    QObject::connect(&fmDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&fmEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFmEnabled(int)));
    QObject::connect(&fmEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&fmEnvAmountSelect, SIGNAL(valueChanged(int)), this, SLOT(setFmEnvAmount(int)));
    QObject::connect(&fmEnvAmountSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&fmEnvelopeEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFmEnvelopeEnabled(int)));
    QObject::connect(&fmEnvelopeEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&fmLfoAmountSelect, SIGNAL(valueChanged(int)), this, SLOT(setFmLfoAmount(int)));
    QObject::connect(&fmLfoAmountSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&fmLfoEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFmLfoEnabled(int)));
    QObject::connect(&fmLfoEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFocus()));
}

void FmBox::setFmDepth(int i) {
    noteFactory->setFmDepth(((double)i)*100);
}

void FmBox::setFmEnabled(int state) {
    noteFactory->setFmEnabled(state == Qt::Checked);
}

void FmBox::setFmEnvelopeEnabled(int state) {
    noteFactory->setFmEnvelopeEnabled(state == Qt::Checked);
}

void FmBox::setFmEnvAmount(int i) {
    noteFactory->setFmEnvAmount(((double)i)/100);
}

void FmBox::setFmLfoEnabled(int state) {
    noteFactory->setFmLfoEnabled(state == Qt::Checked);
}

void FmBox::setFmLfoAmount(int i) {
    noteFactory->setFmLfoAmount(((double)i)/100);
}
