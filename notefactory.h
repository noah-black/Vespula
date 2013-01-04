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

using namespace std;

class NoteFactory {
	public:
		NoteFactory();
        Note *getNote(double freq, enum note n);
		void setWaveform(string i);
		void setLevel(double i);
		void setFmDepth(double i);
        void setFmEnabled(bool fmEnabled);
        void setFmEnvelopeEnabled(bool fmEnvelopeEnabled);
        void setFmEnvAmount(double i);
		vector<string> *getWaveforms();
        Envelope *getEnvelope(int i);
	protected:
        double fmDepth;
        double fmEnvAmount;
		void initMaps();

		map<string, waveformType> waveforms;

        bool fmEnabled;
        bool fmEnvelopeEnabled;

        waveformType currentSound;

        vector<Envelope*> envelopes; 
};

#endif
