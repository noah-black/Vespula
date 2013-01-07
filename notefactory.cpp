#include "notefactory.h"
using namespace std;

NoteFactory::NoteFactory(WaveTable *waveTable) : 
    waveTable(waveTable)
{
    envelopes.push_back(new Envelope(0, 0, 1, 0));
    envelopes.push_back(new Envelope(0, 0, 1, 0));
    lfos.push_back(new LFO(waveTable));
    fmEnabled = false;
    fmEnvelopeEnabled = false;
    fmLfoEnabled = false;
    fmDepth = 0;
    fmEnvAmount = 0;
    fmLfoAmount = 0;
    currentSound = &WaveTable::sawtooth;
}

Note *NoteFactory::getNote(double freq, enum note n) {
    Note *note;
    if(fmEnabled) {
        FM *fm = new FM(waveTable, &currentSound, freq, &fmDepth);
	    note = new Note(fm, envelopes[0], freq, n);
        if(fmLfoEnabled)
            fm->addLfoConnection(new LfoConnection(lfos[0], &fmLfoAmount));
        if(fmEnvelopeEnabled)
            note->addEnvelopeConnection(new EnvelopeConnection(envelopes[1], fm, &fmEnvAmount));
    }
    else
	    note = new Note(new Oscillator(waveTable, &currentSound, freq), envelopes[0], freq, n);
    return note;
}

void NoteFactory::setWaveform(waveformType waveform) {
    currentSound = waveform;
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

void NoteFactory::setFmEnvAmount(double i) {
    fmEnvAmount = i;
}

void NoteFactory::setFmLfoEnabled(bool fmLfoEnabled) {
    this->fmLfoEnabled = fmLfoEnabled;
}

void NoteFactory::setFmLfoAmount(double i) {
    fmLfoAmount = i;
}

Envelope *NoteFactory::getEnvelope(int i) {
    return envelopes[i];
}

LFO *NoteFactory::getLfo(int i) {
    return lfos[i];
}

void NoteFactory::advanceLfos() {
    vector<LFO*>::const_iterator iter;
    for (iter=lfos.begin(); iter != lfos.end(); ++iter) {
        (*iter)->advance();
    }
}
