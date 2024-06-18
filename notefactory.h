#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H
#include "filter.h"
#include "filterproxy.h"
#include "fm.h"
#include "lfo.h"
#include "lfoconnection.h"
#include "note.h"
#include "oscillator.h"
#include "oscillators.h"
#include "soundprocessor.h"
#include "wavetable.h"
#include <QObject>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

class NoteFactory {
public:
  NoteFactory(WaveTable *waveTable);
  ~NoteFactory();
  Note *getNote(double freq, enum note n, double velocity = 1);
  Oscillator *getOscillator(double freq);
  Oscillator *getOscillator(double freq, waveformType waveform);
  void prepareNote(Note *note);
  void setWaveform(waveformType waveform);
  void setLevel(double i);
  void setFmDepth(double i);
  void setFmEnabled(bool fmEnabled);
  void setFmEnvelopeEnabled(bool fmEnvelopeEnabled);
  void setFmEnvAmount(double i);
  void setFmLfoEnabled(bool fmLfoEnabled);
  void setFmLfoAmount(double i);
  void setFilterEnvAmount(double i);
  waveformType getWaveform();
  void advanceLfos();
  Envelope *getEnvelope(int i);
  LFO *getLfo(int i);
  Filter *getFilter(int i);

protected:
  WaveTable *waveTable;
  double fmDepth;
  double fmEnvAmount;
  double fmLfoAmount;

  bool fmEnabled;
  bool fmEnvelopeEnabled;
  bool fmLfoEnabled;

  double filterEnvAmount;

  bool filterEnvEnabled;

  waveformType currentSound;

  std::vector<Envelope *> envelopes;
  std::vector<LFO *> lfos;
  std::vector<Filter *> filters;
};

#endif
