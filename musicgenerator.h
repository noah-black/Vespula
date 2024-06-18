#ifndef MUSIC_GENERATOR_H
#define MUSIC_GENERATOR_H

#include "keyboard.h"
#include "note.h"
#include "notefactory.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

struct PossibleNote {
  enum note n;
  int prob;
  PossibleNote(enum note n = n1, int prob = 1) : n(n), prob(prob) {}
};

class MusicGenerator {
public:
  MusicGenerator(Keyboard **keyboard, NoteFactory *noteFactory,
                 WaveTable *waveTable);
  void advance();

private:
  Keyboard **keyboard;
  NoteFactory *noteFactory;
  std::vector<std::vector<PossibleNote>> notes;
  std::vector<waveformType> waveforms;
  WaveTable *waveTable;
};

#endif
