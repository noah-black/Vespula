#include "notefactory.h"

NoteFactory::NoteFactory(WaveTable *waveTable) : 
    waveTable(waveTable)
{
    envelopes.push_back(new Envelope(0, 0, 1, 0));
    envelopes.push_back(new Envelope(0, 0, 1, 0));
    lfos.push_back(new LFO(waveTable));
    filters.push_back(new Filter());
    fmEnabled = false;
    fmEnvelopeEnabled = false;
    fmLfoEnabled = false;
    filterEnvEnabled = true;
    fmDepth = 0;
    fmEnvAmount = 0;
    fmLfoAmount = 0;
    filterEnvAmount = 0;
    currentSound = &WaveTable::sawtooth;
}

Note *NoteFactory::getNote(double freq, enum note n, double velocity) {
    Note * note;
    note = new Note(getOscillator(freq), envelopes[0], freq, n, velocity);
    if(filterEnvEnabled) {
        FilterProxy *filter = new FilterProxy(filters[0]);
        note->addEnvelopeConnection(new EnvelopeConnection(envelopes[1], filter, &filterEnvAmount));
        note->addNoteEffect(filter);
    }
    
    prepareNote(note);
    return note;
}

NoteFactory::~NoteFactory() {
    std::vector<Envelope*>::iterator eit;
    std::vector<LFO*>::iterator lit;
    for(eit = envelopes.begin(); eit != envelopes.end(); ++eit) {
        delete (*eit);
    }
    for(lit = lfos.begin(); lit != lfos.end(); ++lit) {
        delete (*lit);
    }
}

Oscillator *NoteFactory::getOscillator(double freq) {
    return getOscillator(freq, currentSound);
}

Oscillator *NoteFactory::getOscillator(double freq, waveformType waveform) {
    Oscillator *oscillator;
    if(fmEnabled) {
        FM *fm = new FM(waveTable, waveform, freq, &fmDepth);
        if(fmLfoEnabled)
            fm->addLfoConnection(new LfoConnection(lfos[0], fmLfoAmount));
        oscillator = (Oscillator*)fm;
    }
    else
	    oscillator = new Oscillator(waveTable, waveform, freq);
    return oscillator;
}

void NoteFactory::prepareNote(Note *note) {
        if(fmEnabled && fmEnvelopeEnabled)
            note->addEnvelopeConnection(new EnvelopeConnection(envelopes[1], (FM*)note->getOscillator(), &fmEnvAmount));
}

void NoteFactory::setWaveform(waveformType waveform) {
    currentSound = waveform;
}

waveformType NoteFactory::getWaveform() {
    return currentSound;
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

void NoteFactory::setFilterEnvAmount(double i) {
    filterEnvAmount = i;
}

Envelope *NoteFactory::getEnvelope(int i) {
    return envelopes[i];
}

LFO *NoteFactory::getLfo(int i) {
    return lfos[i];
}

Filter *NoteFactory::getFilter(int i) {
    return filters[i];
}

void NoteFactory::advanceLfos() {
    std::vector<LFO*>::const_iterator iter;
    for (iter=lfos.begin(); iter != lfos.end(); ++iter) {
        (*iter)->advance();
    }
}
