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
	public slots:
		void done();
		void changeWaveform(int value);
		void setTranspose(int value);
	private:
		void initMaps();
		Keyboard keyboard;
		void fillFrame(char *buffer, int i, int sample);
		enum program_state state;
		map<int, enum note> keyMap;
		int buffersize;
		snd_pcm_t *handle;
		snd_pcm_uframes_t frames;
	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
	

};

#endif
