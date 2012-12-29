#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#define SAMPLE_RATE 44100.0

#include <alsa/asoundlib.h>

using namespace std;

class SoundManager{
	public:
		SoundManager();
		~SoundManager();
        void writeSample(int sample);
		void done();
	private:
	    snd_pcm_uframes_t hw_buffer;
		void configureSoundDevice();
	    char *buffer;
        int bufferIndex;
        int counter; // debugging thing, remove

		snd_pcm_uframes_t frames;
		snd_pcm_t *handle;
};

#endif
