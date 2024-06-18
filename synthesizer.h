#ifndef SYNTH_H
#define SYNTH_H

#include "chorus.h"
#include "envelopebox.h"
#include "filter.h"
#include "filterbox.h"
#include "fmbox.h"
#include "keyboard.h"
#include "lfo.h"
#include "lfobox.h"
#include "looper.h"
#include "looperbox.h"
#include "lpf.h"
#include "musicgenerator.h"
#include "note.h"
#include "notefactory.h"
#include "soundmanager.h"
#include "vibrato.h"
#include "vibratobox.h"
#include "waveformcombobox.h"
#include "wavetable.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <cmath>
#include <map>
#include <vector>

enum class ProgramState { NOT_RUNNING, RUNNING, QUITTING };

class Synthesizer : public QMainWindow {
  Q_OBJECT
public:
  Synthesizer();
  void start();
  Keyboard *getCurrentKeyboard();
public slots:
  void done();
  void changeWaveform(int value);
  void setTranspose(int value);
  void setLevel(int i);
  void setMonophonic(int state);

private:
  void prepareGui();
  WaveTable waveTable;
  NoteFactory noteFactory;
  Looper looper;
  Keyboard normalKeyboard;
  Keyboard *keyboard;
  SoundProcessor *main;
  SoundManager soundManager;
  Vibrato vibrato;
  Chorus chorus;
  LPF lpf;
  void initMaps();
  std::map<int, enum note> keyMap;
  std::vector<SoundEffect *> effects;
  ProgramState state;

  QFrame mainArea;

  EnvelopeBox envelopeBox;
  EnvelopeBox freeEnvelopeBox;
  LfoBox lfoBox;
  FilterBox filterBox;

  VibratoBox vibratoBox;

  FmBox fmBox;

  QLabel waveformSelectLabel;
  WaveformComboBox waveformSelect;
  QLabel transposeSelectLabel;
  QSpinBox transposeSelect;
  QLabel levelSelectLabel;
  QSlider levelSelect;
  LooperBox looperBox;
  QCheckBox monophonicEnabled;
  QLabel monophonicLabel;

  QGridLayout layout;
  MusicGenerator generator;

  double level;

protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
};

#endif
