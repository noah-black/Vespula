#ifndef MUSIC_GENERATOR_H
#define MUSIC_GENERATOR_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "keyboard.h"
#include "note.h"
#include "notefactory.h"

struct PossibleNote
{
    enum note n;
    int prob;
    PossibleNote(enum note n = n1, int prob = 1) : n(n), prob(prob) {}
};

class MusicGenerator {
    public:
        MusicGenerator(Keyboard **keyboard, NoteFactory *noteFactory, WaveTable *waveTable);
        void advance();
    private:
        Keyboard **keyboard;
        NoteFactory *noteFactory;
        vector< vector<PossibleNote> > notes;
        vector<waveformType> waveforms;
        WaveTable *waveTable;
};

#endif
