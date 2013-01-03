#include "notefactory.h"

using namespace std;

NoteFactory::NoteFactory(Envelope *envelope):
    envelope(envelope)
{
    fmEnabled = false;
    fmDepth = 0;
    currentSound = Oscillators::sawtooth;
    initMaps();
}

Note *NoteFactory::getNote(double freq, enum note n) {
    Note *note;
    if(fmEnabled) {
        FM *fm = new FM(&currentSound, freq, &fmDepth);
	    note = new Note(fm, envelope, freq, n);
        if(fmModulatorEnabled)
            note->addEnvelopeConnection(new EnvelopeConnection(envelope, fm, 1.0));
    }
    else
	    note = new Note(new Oscillator(&currentSound, freq), envelope, freq, n);
    return note;
}

void NoteFactory::setWaveform(string i) {
    currentSound = waveforms[i];
}

void NoteFactory::setFmDepth(double i) {
    fmDepth = i;
}

void NoteFactory::setFmEnabled(bool fmEnabled) {
    this->fmEnabled = fmEnabled;
}

void NoteFactory::setFmModulatorEnabled(bool fmModulatorEnabled) {
    this->fmModulatorEnabled = fmModulatorEnabled;
}

vector<string> *NoteFactory::getWaveforms() {
    vector<string> *waveformList = new vector<string>();
    map<string, waveformType>::const_iterator iter;
    for (iter=waveforms.begin(); iter != waveforms.end(); ++iter) {
        waveformList->push_back(iter->first);
    }
    return waveformList;
}

void NoteFactory::initMaps() {
    waveforms["Sawtooth"] = Oscillators::sawtooth;
    waveforms["Triangle"] = Oscillators::triangle;
    waveforms["Square"] = Oscillators::square;
    waveforms["Sine"] = Oscillators::sine;
}
