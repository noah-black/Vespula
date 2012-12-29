#include "synthesizer.h"

Synthesizer::Synthesizer() : looper(2),
    normalKeyboard(),
    keyboard(&normalKeyboard),
    vibrato(&normalKeyboard, 0.1, 0),
    chorus(&vibrato, 1, 100),
    lpf(&vibrato),
    mainArea(this),
    envelopeBox(&keyboard, &mainArea),
    vibratoBox(&vibrato, &mainArea),
    fmBox(&keyboard, &mainArea),
    waveformSelectLabel(&mainArea),
    waveformSelect(&mainArea),
    transposeSelectLabel(&mainArea),
    transposeSelect(&mainArea),
    levelSelectLabel(&mainArea),
    levelSelect(&mainArea) {
        initMaps();
        state = NOT_RUNNING;
        main = &vibrato;
        prepareGui();
    }

void Synthesizer::start() {
    int sample;
    state = RUNNING;
    while(state == RUNNING) {
        sample = (main->getSample()*CEILING);
        for(vector<SoundEffect*>::iterator it = soundEffects.begin(); it != soundEffects.end(); ++it) {
            sample = (*it)->getSample(sample);
        }
        soundManager.writeSample(sample);
    }
}

void Synthesizer::prepareGui() {
    vector<Note*> waveforms = getWaveforms();
    for(vector<Note*>::iterator it = waveforms.begin(); it != waveforms.end(); ++it)
        waveformSelect.addItem(QString::fromStdString((*it)->getName()));

    waveformSelectLabel.setText("Waveform: ");

    transposeSelectLabel.setText("Transpose: ");
    transposeSelect.setRange(-12, 12);
    transposeSelect.setSingleStep(1);

    levelSelectLabel.setText("Level");
    levelSelect.setRange(0, 100);
    levelSelect.setValue(10);

    layout.addWidget(&waveformSelectLabel, 0, 0, 1, 1);
    layout.addWidget(&waveformSelect, 0, 1, 1, 1);
    layout.addWidget(&transposeSelectLabel, 1, 0, 1, 1);
    layout.addWidget(&transposeSelect, 1, 1, 1, 1);
    layout.addWidget(&levelSelectLabel, 1, 2, 1, 1);
    layout.addWidget(&levelSelect, 0, 2, 1, 1);
    layout.addWidget(&envelopeBox, 0, 3, -1, 1);
    layout.addWidget(&vibratoBox, 0, 4, -1, 1);
    layout.addWidget(&fmBox, 0, 5, -1, 1);

    mainArea.setLayout(&layout);
    setCentralWidget(&mainArea);

    show();
    setFocus();

    QObject::connect(&waveformSelect, SIGNAL(activated(int)), this, SLOT(changeWaveform(int)));
    QObject::connect(&waveformSelect, SIGNAL(activated(int)), this, SLOT(setFocus()));

    QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), this, SLOT(setTranspose(int)));
    QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

    QObject::connect(&levelSelect, SIGNAL(valueChanged(int)), this, SLOT(setLevel(int)));
    QObject::connect(&levelSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

}

void Synthesizer::keyPressEvent(QKeyEvent *event) {
    setFocus();
    int key = event->key();
    if(key >= Qt::Key_1 && key <= Qt::Key_9) {
        if ((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier)
            keyboard->setTransposeInKey(key - Qt::Key_1);
        else
            keyboard->setOctave(key - Qt::Key_1 - 4);
    }
    else if(!event->isAutoRepeat() && keyMap.find(key) != keyMap.end()) {
        keyboard->playNote(keyMap[key]);
    }
    else
        event->ignore();
}

void Synthesizer::keyReleaseEvent(QKeyEvent *event) {
    setFocus();
    if(!event->isAutoRepeat() && keyMap.find(event->key()) != keyMap.end()) {
        keyboard->releaseNote(keyMap[event->key()]);
    }
    else
        event->ignore();
}

void Synthesizer::done() {
    state = QUITTING;
}

void Synthesizer::changeWaveform(int i) {
    keyboard->setWaveform(i);
}

void Synthesizer::setTranspose(int i) {
    keyboard->setTranspose(i);
}

void Synthesizer::setLevel(int i) {
    keyboard->setLevel(((double)i)/1000);
}

void Synthesizer::initMaps() {
    keyMap[Qt::Key_A] = n1;
    keyMap[Qt::Key_W] = s1;
    keyMap[Qt::Key_S] = n2;
    keyMap[Qt::Key_E] = s2;
    keyMap[Qt::Key_D] = n3;
    keyMap[Qt::Key_F] = n4;
    keyMap[Qt::Key_T] = s4;
    keyMap[Qt::Key_G] = n5;
    keyMap[Qt::Key_Y] = s5;
    keyMap[Qt::Key_H] = n6;
    keyMap[Qt::Key_U] = s6;
    keyMap[Qt::Key_J] = n7;
    keyMap[Qt::Key_K] = n8;
    keyMap[Qt::Key_O] = s8;
    keyMap[Qt::Key_L] = n9;
}

vector<Note*> Synthesizer::getWaveforms() {
    return keyboard->getWaveforms();
}
