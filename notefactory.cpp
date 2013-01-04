#include "notefactory.h"

using namespace std;

NoteFactory::NoteFactory()
{
    envelopes.push_back(new Envelope(0, 0, 1, 0));
    envelopes.push_back(new Envelope(0, 0, 1, 0));
    fmEnabled = false;
    fmEnvelopeEnabled = false;
    fmDepth = 0;
    fmEnvAmount = 0;
    currentSound = Oscillators::sawtooth;
    initMaps();
}

Note *NoteFactory::getNote(double freq, enum note n) {
    Note *note;
    if(fmEnabled) {
        FM *fm = new FM(&currentSound, freq, &fmDepth);
	    note = new Note(fm, envelopes[0], freq, n);
        if(fmEnvelopeEnabled)
            note->addEnvelopeConnection(new EnvelopeConnection(envelopes[1], fm, &fmEnvAmount));
    }
    else
	    note = new Note(new Oscillator(&currentSound, freq), envelopes[0], freq, n);
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

void NoteFactory::setFmEnvelopeEnabled(bool fmEnvelopeEnabled) {
    this->fmEnvelopeEnabled = fmEnvelopeEnabled;
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

Envelope *NoteFactory::getEnvelope(int i) {
    return envelopes[i];
}


void NoteFactory::setFmEnvAmount(double i) {
    fmEnvAmount = i;
}
