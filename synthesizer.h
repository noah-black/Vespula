#ifndef SYNTH_H
#define SYNTH_H

#include <math.h>
#include <vector>
#include <map>
#include <alsa/asoundlib.h>
#include <QMainWindow>
#include <QObject>
#include <QGroupBox>
#include <QKeyEvent>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QtConcurrentRun>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QString>
#include "keyboard.h"
#include "sawtooth.h"
#include "note.h"
#include "lpf.h"
#include "vibrato.h"
#include "looper.h"
#include "chorus.h"

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
		~Synthesizer();
		void start();
		vector<Note*> getWaveforms();
	public slots:
		void done();
		void changeWaveform(int value);
		void setTranspose(int value);
		void setAttack(int value);
		void setDecay(int value);
		void setSustain(int value);
		void setRelease(int value);
		void setVibDepth(int value);
		void setVibPeriod(int value);
		void setLevel(int i);
		void setFmDepth(int i);
	private:
		void prepareGui();
		void configureSoundDevice();
		Looper looper;
		Keyboard normalKeyboard;
		Keyboard *keyboard;
		SoundProcessor *main;
		Vibrato vibrato;
		Chorus chorus;
		LPF lpf;
		void initMaps();
		void fillFrame(char *buffer, int i, int sample);
		enum program_state state;
		map<int, enum note> keyMap;

		snd_pcm_uframes_t frames;
		snd_pcm_t *handle;

		QFrame mainArea;
		QGroupBox envelope;
		QSlider attackSelect;
		QSlider decaySelect;
		QSlider sustainSelect;
		QSlider releaseSelect;
		QSlider vibDepthSelect;
		QSlider vibPeriodSelect;
		QSlider levelSelect;
		QSlider fmDepthSelect;
		QComboBox waveformSelect;
		QSpinBox transposeSelect;

		//QHBoxLayout layout;

	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
	

};

#endif
