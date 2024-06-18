#include "synthesizer.h"

Synthesizer::Synthesizer()
    : waveTable(), noteFactory(&waveTable), looper(&noteFactory, 2),
      normalKeyboard(&noteFactory), keyboard(&normalKeyboard),
      vibrato(&keyboard, 0.1, 0), chorus(&vibrato, 0.2, 1000), lpf(&vibrato),
      mainArea(this), envelopeBox(noteFactory.getEnvelope(0), &mainArea),
      freeEnvelopeBox(noteFactory.getEnvelope(1), &mainArea),
      lfoBox(noteFactory.getLfo(0), &mainArea),
      filterBox(noteFactory.getFilter(0), noteFactory.getLfo(0), &noteFactory,
                &mainArea),
      vibratoBox(&vibrato, &mainArea), fmBox(&noteFactory, &mainArea),
      waveformSelectLabel(&mainArea), waveformSelect(&mainArea),
      transposeSelectLabel(&mainArea), transposeSelect(&mainArea),
      levelSelectLabel(&mainArea), levelSelect(&mainArea),
      looperBox(&keyboard, &normalKeyboard, &looper, &mainArea),
      monophonicEnabled(&mainArea), monophonicLabel(&mainArea),
      generator(&keyboard, &noteFactory, &waveTable) {
  level = 0.01;
  initMaps();
  state = ProgramState::NOT_RUNNING;
  main = &vibrato;
  // effects.push_back(noteFactory.getFilter(0));
  prepareGui();
}

void Synthesizer::start() {
  int sample;
  state = ProgramState::RUNNING;
  while (state == ProgramState::RUNNING) {
    sample = (int)(floor((main->getSample() * CEILING) * level) + 0.5);
    for (std::vector<SoundEffect *>::iterator it = effects.begin();
         it != effects.end(); ++it) {
      sample = (*it)->getSample(sample);
    }
    soundManager.writeSample(sample);
    noteFactory.advanceLfos();
    generator.advance();
  }
}

void Synthesizer::prepareGui() {

  waveformSelectLabel.setText("Waveform: ");
  transposeSelectLabel.setText("Transpose: ");
  transposeSelect.setRange(-12, 12);
  transposeSelect.setSingleStep(1);

  levelSelectLabel.setText("Level");
  levelSelect.setRange(0, 100);
  levelSelect.setValue(10);

  monophonicLabel.setText("Monophonic");

  layout.addWidget(&looperBox, 0, 0, 1, 2);
  layout.addWidget(&waveformSelectLabel, 1, 0, 1, 1);
  layout.addWidget(&waveformSelect, 1, 1, 1, 1);
  layout.addWidget(&transposeSelectLabel, 2, 0, 1, 1);
  layout.addWidget(&transposeSelect, 2, 1, 1, 1);
  layout.addWidget(&monophonicLabel, 3, 0, 1, 1);
  layout.addWidget(&monophonicEnabled, 3, 1, 1, 1);

  layout.addWidget(&levelSelectLabel, 3, 2, 1, 1);
  layout.addWidget(&levelSelect, 0, 2, 3, 1);
  layout.addWidget(&envelopeBox, 0, 3, 4, 1);
  layout.addWidget(&vibratoBox, 0, 4, 4, 1);
  layout.addWidget(&fmBox, 0, 5, 4, 1);

  layout.addWidget(&freeEnvelopeBox, 4, 0, 1, 1);
  layout.addWidget(&lfoBox, 4, 1, 1, 1);
  layout.addWidget(&filterBox, 4, 2, 1, 1);

  mainArea.setLayout(&layout);
  setCentralWidget(&mainArea);

  show();
  setFocus();

  QObject::connect(&waveformSelect, SIGNAL(currentIndexChanged(int)), this,
                   SLOT(changeWaveform(int)));
  QObject::connect(&waveformSelect, SIGNAL(currentIndexChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setTranspose(int)));
  QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&levelSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setLevel(int)));
  QObject::connect(&levelSelect, SIGNAL(valueChanged(int)), this,
                   SLOT(setFocus()));

  QObject::connect(&monophonicEnabled, SIGNAL(stateChanged(int)), this,
                   SLOT(setMonophonic(int)));
}

void Synthesizer::keyPressEvent(QKeyEvent *event) {
  setFocus();
  int key = event->key();
  if (key >= Qt::Key_1 && key <= Qt::Key_9) {
    if ((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier)
      keyboard->setTransposeInKey(key - Qt::Key_1);
    else
      keyboard->setOctave(key - Qt::Key_1 - 4);
  } else if (!event->isAutoRepeat() && keyMap.find(key) != keyMap.end()) {
    keyboard->playNote(keyMap[key]);
  } else
    event->ignore();
}

void Synthesizer::keyReleaseEvent(QKeyEvent *event) {
  setFocus();
  if (!event->isAutoRepeat() && keyMap.find(event->key()) != keyMap.end()) {
    keyboard->releaseNote(keyMap[event->key()]);
  } else
    event->ignore();
}

void Synthesizer::done() { state = ProgramState::QUITTING; }

void Synthesizer::changeWaveform(int i) {
  keyboard->setWaveform(waveformSelect.getWaveformType(i));
}

void Synthesizer::setTranspose(int i) { keyboard->setTranspose(i); }

void Synthesizer::setLevel(int i) { level = ((double)i) / 1000; }

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

void Synthesizer::setMonophonic(int state) {
  keyboard->setMonophonic(state == Qt::Checked);
}
