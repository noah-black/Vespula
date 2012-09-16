#include "synthesizer.h"

//Synthesizer::Synthesizer() : keyboard(2), vibrato(&keyboard, 0.1, 0) {
Synthesizer::Synthesizer() : keyboard(2), vibrato(&keyboard, 0.1, 0), chorus(&vibrato, 1, 100) {
	initMaps();
	state = NOT_RUNNING;
	main = &chorus;
	//main = &vibrato;
	//main = &keyboard;
	//main = &lpf;
	configureSoundDevice();
}
void Synthesizer::start() {
	char *buffer;
	unsigned int i;
	int rc;
	int sample;
	buffer = (char *) malloc(frames*4);
	state = RUNNING;
	while(state == RUNNING) {
		for (i = 0; i < frames; i++) {
			sample = main->getSample();
			fillFrame(buffer, i, sample);
		}
		rc = snd_pcm_writei(handle, buffer, frames);
		if (rc == -EPIPE) {
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(handle); } 
		else if (rc < 0) 
			fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
		else if (rc != (unsigned)frames) 
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
	int key = event->key();
	if(key >= Qt::Key_1 && key <= Qt::Key_9) {
		if ((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier)
			keyboard.setTransposeInKey(key - Qt::Key_1);
		else
			keyboard.setOctave(key - Qt::Key_1 - 4);
	}
	else if(!event->isAutoRepeat() && keyMap.find(key) != keyMap.end()) {
		keyboard.playNote(keyMap[key]);
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
	keyboard.setWaveform(i);
}

void Synthesizer::setTranspose(int i) {
	keyboard.setTranspose(i);
}

void Synthesizer::setAttack(int i) {
	keyboard.setAttack(((double)i)/50);
}

void Synthesizer::setDecay(int i) {
	keyboard.setDecay(((double)i)/50);
}

void Synthesizer::setRelease(int i) {
	keyboard.setRelease(((double)i)/50);
}

void Synthesizer::setSustain(int i) {
	keyboard.setSustain(((double)i)/100);
}

void Synthesizer::setVibDepth(int value) {
	vibrato.setDepth(value*100);
}

void Synthesizer::setVibPeriod(int value) {
	vibrato.setPeriod(((double)value)/100);
}

void Synthesizer::configureSoundDevice() {
	unsigned int val;
	int dir, rc;
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
}

void Synthesizer::initMaps() {
	keyMap[Qt::Key_A] = n1;
	keyMap[Qt::Key_W] = s1;
	keyMap[Qt::Key_S] = n2;
	keyMap[Qt::Key_E] = s2;
	keyMap[Qt::Key_D] = n3;
	keyMap[Qt::Key_F] = n4;
	keyMap[Qt::Key_T] = s4;
	keyMap[Qt::Key_G] = n5;
	keyMap[Qt::Key_Y] = s5;
	keyMap[Qt::Key_H] = n6;
	keyMap[Qt::Key_U] = s6;
	keyMap[Qt::Key_J] = n7;
	keyMap[Qt::Key_K] = n8;
	keyMap[Qt::Key_O] = s8;
	keyMap[Qt::Key_L] = n9;
}

vector<Note*> Synthesizer::getWaveforms() {
	return keyboard.getWaveforms();
}

Synthesizer::~Synthesizer() {
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
}
