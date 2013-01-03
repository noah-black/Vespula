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
		NoteFactory(Envelope *envelope);
        Note *getNote(double freq, enum note n);
		void setWaveform(string i);
		void setLevel(double i);
		void setFmDepth(double i);
        void setFmEnabled(bool fmEnabled);
        void setFmModulatorEnabled(bool fmModulatorEnabled);
		vector<string> *getWaveforms();
	protected:
        double fmDepth;
		void initMaps();

		map<string, waveformType> waveforms;

        bool fmEnabled;
        bool fmModulatorEnabled;

        waveformType currentSound;

        Envelope *envelope;
    
};

#endif
