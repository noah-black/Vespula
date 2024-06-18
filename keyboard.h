#ifndef MIXER_H
#define MIXER_H
#include "fm.h"
#include "note.h"
#include "notefactory.h"
#include "oscillator.h"
#include "oscillators.h"
#include "soundprocessor.h"
#include <QObject>
#include <deque>
#include <map>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <string>

class Keyboard : public SoundProcessor {
public:
  Keyboard(NoteFactory *noteFactory);
  ~Keyboard();
  virtual double getSample();
  virtual void playNote(enum note n);
  void playNote(Note *note);
  virtual void releaseNote(enum note n);
  void setOctave(int i);
  void setTransposeInKey(int i);
  void setTranspose(int i);
  void clearAll();
  void setMonophonic(bool monophonic);
  enum note getTransposition(enum note n, int transposeInKey);
  enum note getTransposition(enum note n);
  double getFreq(enum note n, int octave);
  double getFreq(enum note n);
  void cullNotes();
  void setWaveform(waveformType waveform);

protected:
  std::map<enum note, double> freqs;
  bool isNote(char c);
  virtual void releaseNoteInternal(enum note n);
  bool isNatural(enum note n);
  bool isSharp(enum note n);
  enum note getNatural(int n);
  enum note getSharp(int n);
  void initMaps();
  pthread_mutex_t noteMutex;
  pthread_mutex_t lastNoteMutex;
  int getInterval(enum note);
  NoteFactory *noteFactory;

  std::deque<Note *> notes;
  std::map<enum note, Note *> lastNoteFor;

  unsigned int voices;

  int octave;
  int transpose;
  int transposeInKey;
  bool monophonic;
};

#endif
