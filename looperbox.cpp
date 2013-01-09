#include "looperbox.h"

LooperBox::LooperBox(Keyboard **currentKeyboard, Keyboard *normalKeyboard, Looper *looper, QWidget *parent) : 
    QGroupBox(parent),
    currentKeyboard(currentKeyboard),
    normalKeyboard(normalKeyboard),
    looper(looper),
    durationSelect(this),
    durationSelectLabel(this),
    looperEnabled(this),
    looperLabel(this),
    clearButton(this)
{
    durationSelectLabel.setText("Duration(0.1s): ");
    looperLabel.setText("Looper");
    durationSelect.setRange(1, 80);
    durationSelect.setSingleStep(1);
    durationSelect.setValue(20);
    clearButton.setText("Clear");

    layout.addWidget(&looperLabel, 0, 0, 1, 1);
    layout.addWidget(&looperEnabled, 0, 1, 1, 1);
    layout.addWidget(&durationSelectLabel, 1, 0, 1, 1);
    layout.addWidget(&durationSelect, 1, 1, 1, 1);
    layout.addWidget(&clearButton, 2, 1, 1, -1);

    this->setLayout(&layout);

    QObject::connect(&looperEnabled, SIGNAL(stateChanged(int)), this, SLOT(setLooperEnabled(int)));

    QObject::connect(&durationSelect, SIGNAL(valueChanged(int)), this, SLOT(setLooperDuration(int)));

    QObject::connect(&clearButton, SIGNAL(clicked(bool)), this, SLOT(clear(bool)));
}



void LooperBox::setLooperEnabled(int state) {
    (*currentKeyboard) = state == Qt::Checked ? (Keyboard*)looper : normalKeyboard;
}

void LooperBox::setLooperDuration(int value) {
    looper->setDuration((double)value/10.0);
}

void LooperBox::clear(bool value) {
    looper->clear();
}
