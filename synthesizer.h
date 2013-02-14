#ifndef SYNTH_H
#define SYNTH_H

#include <math.h>
#include <vector>
#include <map>
#include <QMainWindow>
#include <QObject> 
#include <QGroupBox> 
#include <QCheckBox> 
#include <QKeyEvent>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QtConcurrentRun>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QString>
#include "keyboard.h"
#include "note.h"
#include "lpf.h"
#include "vibrato.h"
#include "looper.h"
#include "chorus.h"
#include "envelopebox.h"
#include "lfobox.h"
#include "vibratobox.h"
#include "fmbox.h"
#include "soundmanager.h"
#include "notefactory.h"
#include "lfo.h"
#include "wavetable.h"
#include "waveformcombobox.h"
#include "looperbox.h"
#include "musicgenerator.h"
#include "filter.h"
#include "filterbox.h"

using namespace std;

enum program_state {
	NOT_RUNNING,
	RUNNING,
	QUITTING
};

class Synthesizer : public QMainWindow {
	Q_OBJECT
	public:
		Synthesizer();
        void start();
        Keyboard *getCurrentKeyboard();
	public slots:
		void done();
		void changeWaveform(int value);
		void setTranspose(int value);
		void setLevel(int i);
		void setMonophonic(int state);
	private:
		void prepareGui();
        WaveTable waveTable;
        NoteFactory noteFactory;
		Looper looper;
		Keyboard normalKeyboard;
		Keyboard *keyboard;
		SoundProcessor *main;
        SoundManager soundManager;
		Vibrato vibrato;
		Chorus chorus;
		LPF lpf;
        Filter filter;
		void initMaps();
		map<int, enum note> keyMap;
        enum program_state state;

		QFrame mainArea;

		EnvelopeBox envelopeBox;
		EnvelopeBox freeEnvelopeBox;
		LfoBox lfoBox;
		FilterBox filterBox;
        
        VibratoBox vibratoBox;

        FmBox fmBox;

        QLabel waveformSelectLabel;
		WaveformComboBox waveformSelect;
        QLabel transposeSelectLabel;
		QSpinBox transposeSelect;
        QLabel levelSelectLabel;
		QSlider levelSelect;
        LooperBox looperBox;
        QCheckBox monophonicEnabled;
        QLabel monophonicLabel;

	    QGridLayout layout;
        MusicGenerator generator;

        double level;

	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
};

#endif
