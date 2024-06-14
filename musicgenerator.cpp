#include "musicgenerator.h"

MusicGenerator::MusicGenerator(Keyboard **keyboard, NoteFactory *noteFactory, WaveTable *waveTable) : 
    keyboard(keyboard),
    noteFactory(noteFactory),
    waveTable(waveTable)
{
    srand ( time(NULL) );
    notes.push_back(std::vector<PossibleNote>());
    notes.push_back(std::vector<PossibleNote>());
    notes.push_back(std::vector<PossibleNote>());
    notes.push_back(std::vector<PossibleNote>());
    notes.push_back(std::vector<PossibleNote>());
    notes.push_back(std::vector<PossibleNote>());

    notes[0].push_back(PossibleNote(n1, 40));
    notes[0].push_back(PossibleNote(n5, 40));


    notes[1].push_back(PossibleNote(n1, 40));
    notes[1].push_back(PossibleNote(n3, 40));
    notes[1].push_back(PossibleNote(n5, 40));

    notes[2].push_back(PossibleNote(n1, 30));
    notes[2].push_back(PossibleNote(n2, 1));
    notes[2].push_back(PossibleNote(n3, 30));
    notes[2].push_back(PossibleNote(n5, 30));
    notes[2].push_back(PossibleNote(n6, 1));
    notes[2].push_back(PossibleNote(n7, 8));

    notes[3].push_back(PossibleNote(n1, 20));
    notes[3].push_back(PossibleNote(n2, 3));
    notes[3].push_back(PossibleNote(n3, 20));
    notes[3].push_back(PossibleNote(n5, 20));
    notes[3].push_back(PossibleNote(n6, 3));
    notes[3].push_back(PossibleNote(n7, 8));

    notes[4].push_back(PossibleNote(n1, 20));
    notes[4].push_back(PossibleNote(n2, 3));
    notes[4].push_back(PossibleNote(n3, 20));
    notes[4].push_back(PossibleNote(n5, 20));
    notes[4].push_back(PossibleNote(n6, 3));
    notes[4].push_back(PossibleNote(n7, 8));

    notes[5].push_back(PossibleNote(n1, 20));
    notes[5].push_back(PossibleNote(n2, 3));
    notes[5].push_back(PossibleNote(n3, 20));
    notes[5].push_back(PossibleNote(n5, 20));
    notes[5].push_back(PossibleNote(n6, 3));
    notes[5].push_back(PossibleNote(n7, 8));



    waveforms.push_back(&WaveTable::triangle);
    waveforms.push_back(&WaveTable::sine);
    waveforms.push_back(&WaveTable::square);
    waveforms.push_back(&WaveTable::sawtooth);
}

void MusicGenerator::advance() {
    return;
    if(rand() % (int)(SAMPLE_RATE)/12 == 0) {
        int octave, durationInSamples, left, weightTotal;
        unsigned i, j;
        double velocity, freq, freq1, freq2;
        PossibleNote n;
        Note *note1, *note2;
        Oscillator *oscillator1, *oscillator2;
        Envelope *envelope;
        waveformType waveform;

        durationInSamples = rand() % ((int)SAMPLE_RATE * 4) + (int)(SAMPLE_RATE/4);

        weightTotal = 0;
        for(i=0;i<notes.size();i++) {
            for(j=0;j<notes[i].size();j++) {
                weightTotal += notes[i][j].prob;
            }
        }

        left = rand() % weightTotal; 
        for(i=0;i<notes.size();i++) {
            for(j=0;j<notes[i].size();j++) {
                if(left - notes[i][j].prob < 0) {
                    n = notes[i][j];
                    break;
                }
                else
                    left -= notes[i][j].prob;
            }
            if(left - notes[i][j].prob < 0)
                break;
        }

        velocity = ((double)((rand() % 80) + 20))/100;
        octave = i-3;
        freq = (*keyboard)->getFreq(n.n, octave);
        freq1 = freq*(1+(1.0/400.0));
        freq2 = freq*(1-(1.0/400.0));
        envelope = noteFactory->getEnvelope(0);
        waveform = waveforms[rand() % waveforms.size()];
        oscillator1 = new Oscillator(waveTable, waveform, freq1);
        oscillator2 = new Oscillator(waveTable, waveform, freq2);
        oscillator1 = noteFactory->getOscillator(freq1, waveform);
        oscillator2 = noteFactory->getOscillator(freq2, waveform);
        note1 = new Note(oscillator1, envelope, freq1, n.n, velocity);
        note2 = new Note(oscillator2, envelope, freq2, n.n, velocity);
        noteFactory->prepareNote(note1);
        noteFactory->prepareNote(note2);
        note1->setReleaseSample(durationInSamples);
        note2->setReleaseSample(durationInSamples);
        (*keyboard)->playNote(note1);
        (*keyboard)->playNote(note2);
    }
}
