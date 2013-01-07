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
        void setLooperEnabled(int state);
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
		void initMaps();
		map<int, enum note> keyMap;
        enum program_state state;

		QFrame mainArea;

		EnvelopeBox envelopeBox;
		EnvelopeBox freeEnvelopeBox;
		LfoBox lfoBox;
        
        VibratoBox vibratoBox;

        FmBox fmBox;

        QLabel waveformSelectLabel;
		WaveformComboBox waveformSelect;
        QLabel transposeSelectLabel;
		QSpinBox transposeSelect;
        QLabel levelSelectLabel;
		QSlider levelSelect;

        QCheckBox looperEnabled;
        QLabel looperLabel;

	    QGridLayout layout;

        double level;

	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
};

#endif
