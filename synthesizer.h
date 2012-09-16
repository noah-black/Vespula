#ifndef SYNTH_H
#define SYNTH_H

#include <math.h>
#include <vector>
#include <map>
#include <alsa/asoundlib.h>
#include <QWidget>
#include <QObject>
#include <QKeyEvent>
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

class Synthesizer : public QWidget {
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
	private:
		snd_pcm_uframes_t frames;
		void configureSoundDevice();
		Looper keyboard;
		//Keyboard keyboard;
		SoundProcessor *main;
		Vibrato vibrato;
		Chorus chorus;
		//LPF lpf;
		void initMaps();
		void fillFrame(char *buffer, int i, int sample);
		enum program_state state;
		map<int, enum note> keyMap;
		snd_pcm_t *handle;
	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
	

};

#endif
