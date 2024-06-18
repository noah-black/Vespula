#include "filterbox.h"

FilterBox::FilterBox(Filter *filter, LFO *lfo, NoteFactory *noteFactory,
                     QWidget *parent)
    : QGroupBox(parent), filter(filter), lfo(lfo), noteFactory(noteFactory),
      filterLabel(this), cutoffSelect(this), cutoffLabel(this),
      resonanceSelect(this), resonanceLabel(this), cutoffLfoLabel(this),
      cutoffLfoAmountSelect(this), cutoffEnvLabel(this),
      cutoffEnvAmountSelect(this)

{
  filter->addLfoConnection(new LfoConnection(lfo, 0));
  filterLabel.setText("Filter");

  cutoffSelect.setRange(1, 1000);
  cutoffLabel.setText("Cutoff");
  cutoffSelect.setValue(1000);

  resonanceSelect.setRange(0, 100);
  resonanceLabel.setText("Res.");
  resonanceSelect.setValue(0);

  cutoffLfoAmountSelect.setRange(0, 100);
  cutoffLfoLabel.setText("LFO");
  cutoffLfoAmountSelect.setValue(0);

  cutoffEnvAmountSelect.setRange(0, 100);
  cutoffEnvLabel.setText("Env.");
  cutoffEnvAmountSelect.setValue(0);

  layout.addWidget(&filterLabel, 0, 0, 1, -1);
  layout.addWidget(&cutoffSelect, 1, 0, 1, 1);
  layout.addWidget(&cutoffLabel, 2, 0, 1, 1, Qt::AlignHCenter);
  layout.addWidget(&resonanceSelect, 1, 1, 1, 1);
  layout.addWidget(&resonanceLabel, 2, 1, 1, 1, Qt::AlignHCenter);
  layout.addWidget(&cutoffLfoAmountSelect, 1, 2, 1, 1);
  layout.addWidget(&cutoffLfoLabel, 2, 2, 1, 1, Qt::AlignHCenter);
  layout.addWidget(&cutoffEnvAmountSelect, 1, 3, 1, 1);
  layout.addWidget(&cutoffEnvLabel, 2, 3, 1, 1, Qt::AlignHCenter);

  this->setLayout(&layout);

  QObject::connect(&cutoffSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setCutoff(int)));
  QObject::connect(&cutoffSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&resonanceSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setResonance(int)));
  QObject::connect(&resonanceSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&cutoffLfoAmountSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setCutoffLfoAmount(int)));
  QObject::connect(&cutoffLfoAmountSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&cutoffEnvAmountSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setCutoffEnvAmount(int)));
  QObject::connect(&cutoffEnvAmountSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));
}

void FilterBox::setCutoff(int value) {
  filter->setCutoff(((double)value) / 1000);
}

void FilterBox::setResonance(int value) {
  filter->setResonance(((double)value) / 100);
}

void FilterBox::setCutoffLfoAmount(int i) {
  filter->setLfoAmount(((double)i) / 100);
}

void FilterBox::setCutoffEnvAmount(int i) {
  noteFactory->setFilterEnvAmount(((double)i) / 100);
}
