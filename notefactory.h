#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H 
#include <QObject>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <stdio.h>
#include "fm.h"
#include "soundprocessor.h"
#include "oscillators.h"
#include "oscillator.h"
#include "note.h"
#include "lfo.h"
#include "lfoconnection.h"
#include "wavetable.h"

using namespace std;

class NoteFactory {
	public:
        NoteFactory(WaveTable *waveTable);
        Note *getNote(double freq, enum note n);
		void setWaveform(waveformType waveform);
		void setLevel(double i);
		void setFmDepth(double i);
        void setFmEnabled(bool fmEnabled);
        void setFmEnvelopeEnabled(bool fmEnvelopeEnabled);
        void setFmEnvAmount(double i);
        void setFmLfoEnabled(bool fmLfoEnabled);
        void setFmLfoAmount(double i);
        void advanceLfos();
        Envelope *getEnvelope(int i);
        LFO *getLfo(int i);
	protected:
        WaveTable *waveTable;
        double fmDepth;
        double fmEnvAmount;
        double fmLfoAmount;

        bool fmEnabled;
        bool fmEnvelopeEnabled;
        bool fmLfoEnabled;

        waveformType currentSound;

        vector<Envelope*> envelopes; 
        vector<LFO*> lfos; 
};

#endif
