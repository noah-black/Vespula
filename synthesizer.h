#ifndef SYNTH_H
#define SYNTH_H

#include <vector>
#include <map>
#include <alsa/asoundlib.h>
#include "note.h"
#include "keyboard.h"

#define PI		3.14159265358979323846

using namespace std;

enum program_state {
	RUNNING,
	QUITTING
};

class Synthesizer {
	public:
		Synthesizer();
		~Synthesizer();
		void start();
	private:
		Keyboard keyboard;
		void checkInput(void);
		void fillFrame(char *buffer, int i, int sample);
		int rc;
		enum program_state state;
		int buffersize;
		snd_pcm_t *handle;
		snd_pcm_uframes_t frames;
	

};

#endif
