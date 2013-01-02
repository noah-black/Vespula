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
#include <jack/jack.h>
#include "keyboard.h"
#include "note.h"
#include "lpf.h"
#include "vibrato.h"
#include "looper.h"
#include "chorus.h"
#include "soundeffect.h"
#include "envelopebox.h"
#include "vibratobox.h"
#include "fmbox.h"
#include "soundmanager.h"
#include "notefactory.h"

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
		vector<string> *getWaveforms();
        void start();
        Keyboard *getCurrentKeyboard();
	public slots:
		void done();
		void changeWaveform(int value);
		void setTranspose(int value);
		void setLevel(int i);
	private:
		void prepareGui();
		vector<string> *waveforms;
		vector<SoundEffect*> soundEffects;
        Envelope envelope;
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
        
        VibratoBox vibratoBox;

        FmBox fmBox;

        QLabel waveformSelectLabel;
		QComboBox waveformSelect;
        QLabel transposeSelectLabel;
		QSpinBox transposeSelect;
        QLabel levelSelectLabel;
		QSlider levelSelect;

	    QGridLayout layout;

        double level;

	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
};

#endif
