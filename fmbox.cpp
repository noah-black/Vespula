#include "fmbox.h"

FmBox::FmBox(NoteFactory *noteFactory, QWidget *parent) : 
    QGroupBox(parent),
    noteFactory(noteFactory),
    fmLabel(this),
    fmDepthSelect(this),
    fmEnabled(this)
{
    fmLabel.setText("FM");

    fmDepthSelect.setRange(0, 100);

    fmLayout.addWidget(&fmLabel, 0, 0, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmDepthSelect, 1, 0, 1, 1, Qt::AlignHCenter);
    fmLayout.addWidget(&fmEnabled, 2, 0, 1, 1, Qt::AlignHCenter);

    this->setLayout(&fmLayout);

    QObject::connect(&fmDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFmDepth(int)));
    QObject::connect(&fmDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&fmEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFmEnabled(int)));
    QObject::connect(&fmEnabled, SIGNAL(stateChanged(int)), this, SLOT(setFocus()));
}

void FmBox::setFmDepth(int i) {
    noteFactory->setFmDepth(((double)i)*100);
}

void FmBox::setFmEnabled(int state) {
    noteFactory->setFmEnabled(state == Qt::Checked);
}
