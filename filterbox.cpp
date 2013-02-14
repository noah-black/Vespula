#include "filterbox.h"

FilterBox::FilterBox(Filter *filter, QWidget *parent) :
    QGroupBox(parent),
    filter(filter),
    filterLabel(this),
    cutoffSelect(this),
    cutoffLabel(this),
    resonanceSelect(this),
    resonanceLabel(this)
{
    filterLabel.setText("Filter");

    cutoffSelect.setRange(1, 1000);
    cutoffLabel.setText("Cutoff");
    cutoffSelect.setValue(1000);

    resonanceSelect.setRange(0, 100);
    resonanceLabel.setText("Res.");
    resonanceSelect.setValue(0);

    layout.addWidget(&filterLabel, 0, 0, 1, -1);
    layout.addWidget(&cutoffSelect, 1, 0, 1, 1);
    layout.addWidget(&cutoffLabel, 2, 0, 1, 1, Qt::AlignHCenter);
    layout.addWidget(&resonanceSelect, 1, 1, 1, 1);
    layout.addWidget(&resonanceLabel, 2, 1, 1, 1, Qt::AlignHCenter);
    this->setLayout(&layout);

    QObject::connect(&cutoffSelect, SIGNAL(valueChanged(int)), this, SLOT(setCutoff(int)));
    QObject::connect(&cutoffSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&resonanceSelect, SIGNAL(valueChanged(int)), this, SLOT(setResonance(int)));
    QObject::connect(&resonanceSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));
}

void FilterBox::setCutoff(int value) {
    filter->setCutoff(((double)value)/1000);
}

void FilterBox::setResonance(int value) {
    filter->setResonance(((double)value)/100);
}
