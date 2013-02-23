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
#include "filter.h"
#include "wavetable.h"
#include "filterproxy.h"

using namespace std;

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

        vector<Envelope*> envelopes; 
        vector<LFO*> lfos; 
        vector<Filter*> filters; 
};

#endif
