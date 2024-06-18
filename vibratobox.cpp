#include "vibratobox.h"

VibratoBox::VibratoBox(Vibrato *vibrato, QWidget *parent)
    : QGroupBox(parent), vibrato(vibrato), vibratoLabel(this),
      vibDepthSelect(this), vibDepthLabel(this), vibPeriodSelect(this),
      vibPeriodLabel(this) {
  vibratoLabel.setText("Vibrato");

  vibDepthSelect.setRange(0, 100);
  vibDepthLabel.setText("Depth");

  vibPeriodSelect.setRange(1, 100);
  vibPeriodSelect.setValue(10);
  vibPeriodLabel.setText("Period");

  vibLayout.addWidget(&vibratoLabel, 0, 0, 1, -1);
  vibLayout.addWidget(&vibDepthSelect, 1, 0);
  vibLayout.addWidget(&vibDepthLabel, 2, 0, 1, 1, Qt::AlignHCenter);
  vibLayout.addWidget(&vibPeriodSelect, 1, 1);
  vibLayout.addWidget(&vibPeriodLabel, 2, 1, 1, 1, Qt::AlignHCenter);

  this->setLayout(&vibLayout);

  QObject::connect(&vibDepthSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setVibDepth(int)));
  QObject::connect(&vibDepthSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&vibPeriodSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setVibPeriod(int)));
  QObject::connect(&vibPeriodSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));
}

void VibratoBox::setVibDepth(int value) { vibrato->setDepth(value * 100); }

void VibratoBox::setVibPeriod(int value) {
  vibrato->setPeriod(((double)value) / 100);
}
