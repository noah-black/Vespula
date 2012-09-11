#include "synthesizer.h"


Synthesizer::Synthesizer() {
	unsigned int val;
	int dir, rc;
	initMaps();
	state = NOT_RUNNING;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t hw_buffer;
	rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	if (rc < 0) {
		fprintf(stderr, 
				"unable to open pcm device: %s\n",
				snd_strerror(rc));
		exit(1);
	}
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(handle, params);
	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(handle, params, 2);
	val = SAMPLE_RATE;
	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);
	frames = 32;
	hw_buffer = frames * 32;
	snd_pcm_hw_params_set_buffer_size_max(handle, params, &hw_buffer);
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
	rc = snd_pcm_hw_params(handle, params);
	if (rc < 0) {
		fprintf(stderr, 
				"unable to set hw parameters: %s\n",
				snd_strerror(rc));
		exit(1);
	}
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	buffersize = frames * 4; /* 2 bytes/sample, 2 channels */
}

void Synthesizer::initMaps() {
	keyMap[Qt::Key_A] = a;
	keyMap[Qt::Key_W] = aSharp;
	keyMap[Qt::Key_S] = b;
	keyMap[Qt::Key_E] = c;
	keyMap[Qt::Key_D] = cSharp;
	keyMap[Qt::Key_F] = d;
	keyMap[Qt::Key_T] = dSharp;
	keyMap[Qt::Key_G] = e;
	keyMap[Qt::Key_Y] = f;
	keyMap[Qt::Key_H] = fSharp;
	keyMap[Qt::Key_U] = g;
	keyMap[Qt::Key_J] = gSharp;
	keyMap[Qt::Key_K] = a2;
	keyMap[Qt::Key_O] = aSharp2;
	keyMap[Qt::Key_L] = b2;
}

void Synthesizer::start() {
	char *buffer;
	unsigned int i;
	int rc;
	int sample;
	buffer = (char *) malloc(buffersize);
	state = RUNNING;
	while(state == RUNNING) {
		for (i = 0; i < frames; i++) {
			sample = keyboard.getSample();
			fillFrame(buffer, i, sample);
		}
		rc = snd_pcm_writei(handle, buffer, frames);
		if (rc == -EPIPE) {
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(handle);
		} 
		else if (rc < 0) 
			fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
		else if (rc != frames) 
			fprintf(stderr, "short write, write %d frames\n", rc);
		if(state == QUITTING)
			break;
	}
	free(buffer);
}

void Synthesizer::fillFrame(char *buffer, int i, int sample) {
	buffer[i * 4] = sample & 255;
	buffer[(i * 4) + 2] = sample & 255;
	buffer[(i * 4) + 1] = sample >> 8;
	buffer[(i * 4) + 3] = sample >> 8;
}

void Synthesizer::keyPressEvent(QKeyEvent *event) {
	setFocus();
	if(!event->isAutoRepeat() && keyMap.find(event->key()) != keyMap.end()) {
		keyboard.playNote(keyMap[event->key()]);
	}
	else
		event->ignore();
}

void Synthesizer::keyReleaseEvent(QKeyEvent *event) {
	setFocus();
	if(!event->isAutoRepeat() && keyMap.find(event->key()) != keyMap.end()) {
		keyboard.releaseNote(keyMap[event->key()]);
	}
	else
		event->ignore();
}

void Synthesizer::done() {
	state = QUITTING;
}

void Synthesizer::changeWaveform(int i) {
	if(i == 0)
		keyboard.setSawtooth();
	else if(i == 1)
		keyboard.setTriangle();
	else if(i == 2)
		keyboard.setSquare();
	else if(i == 3)
		keyboard.setSine();
}

void Synthesizer::setTranspose(int i) {
	keyboard.setTranspose(i);
}

Synthesizer::~Synthesizer() {
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
}
