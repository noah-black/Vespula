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
		void setWaveform(string i);
		void setLevel(double i);
		void setFmDepth(double i);
        void setFmEnabled(bool fmEnabled);
        void setFmEnvelopeEnabled(bool fmEnvelopeEnabled);
        void setFmEnvAmount(double i);
        void advanceLfos();
		vector<string> *getWaveforms();
        Envelope *getEnvelope(int i);
        LFO *getLfo(int i);
	protected:
        WaveTable *waveTable;
        double fmDepth;
        double fmEnvAmount;
        double fmLfoAmount;
		void initMaps();

		map<string, waveformType> waveforms;

        bool fmEnabled;
        bool fmEnvelopeEnabled;

        waveformType currentSound;

        vector<Envelope*> envelopes; 
        vector<LFO*> lfos; 
};

#endif
