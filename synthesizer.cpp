#include "synthesizer.h"

Synthesizer::Synthesizer() : looper(2),
 normalKeyboard(),
 keyboard(&looper),
 vibrato(keyboard, 0.1, 0),
 chorus(&vibrato, 1, 100),
 lpf(&chorus),
 mainArea(this),
 envelope(&mainArea),
 envelopeLabel(&envelope),
 attackSelect(&envelope),
 attackLabel(&envelope),
 decaySelect(&envelope),
 decayLabel(&envelope),
 sustainSelect(&envelope),
 sustainLabel(&envelope),
 releaseSelect(&envelope),
 releaseLabel(&envelope),
 vibratoSection(&mainArea),
 vibratoLabel(&vibratoSection),
 vibDepthSelect(&vibratoSection),
 vibDepthLabel(&vibratoSection),
 vibPeriodSelect(&vibratoSection),
 vibPeriodLabel(&vibratoSection),
 waveformSelect(&mainArea),
 transposeSelect(&mainArea) {
	initMaps();
	state = NOT_RUNNING;
	main = &lpf;
	configureSoundDevice();
	prepareGui();
}
void Synthesizer::start() {
	char *buffer;
	unsigned int i;
	int rc;
	int sample;
	buffer = new char[frames*4];
	state = RUNNING;
	while(state == RUNNING) {
		for (i = 0; i < frames; i++) {
			sample = (main->getSample()*CEILING);
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
	}
    delete[] buffer;
}

void Synthesizer::prepareGui() {
	vector<Note*> waveforms = getWaveforms();
	for(vector<Note*>::iterator it = waveforms.begin(); it != waveforms.end(); ++it)
		waveformSelect.addItem(QString::fromStdString((*it)->getName()));

	transposeSelect.setRange(-12, 12);
	transposeSelect.setSingleStep(1);

    envelopeLabel.setText("Envelope");

	attackSelect.setRange(0, 100);
    attackLabel.setText("A");

	decaySelect.setRange(0, 100);
    decayLabel.setText("D");

	sustainSelect.setRange(0, 100);
	sustainSelect.setValue(100);
    sustainLabel.setText("S");

	releaseSelect.setRange(0, 100);
    releaseLabel.setText("R");

    vibratoLabel.setText("Vibrato");

	vibDepthSelect.setRange(0, 100);
    vibDepthLabel.setText("Depth");

	vibPeriodSelect.setRange(1, 100);
    vibPeriodLabel.setText("Period");

	levelSelect.setRange(0, 100);

	fmDepthSelect.setRange(0, 100);

	envLayout.addWidget(&envelopeLabel, 0, 0, 1, -1);
	envLayout.addWidget(&attackSelect, 1, 0);
	envLayout.addWidget(&attackLabel, 2, 0, 1, 1, Qt::AlignHCenter);
	envLayout.addWidget(&decaySelect, 1, 1);
	envLayout.addWidget(&decayLabel, 2, 1, 1, 1, Qt::AlignHCenter);
	envLayout.addWidget(&sustainSelect, 1, 2);
	envLayout.addWidget(&sustainLabel, 2, 2, 1, 1, Qt::AlignHCenter);
	envLayout.addWidget(&releaseSelect, 1, 3);
	envLayout.addWidget(&releaseLabel, 2, 3, 1, 1, Qt::AlignHCenter);

	vibLayout.addWidget(&vibratoLabel, 0, 0, 1, -1);
	vibLayout.addWidget(&vibDepthSelect, 1, 0);
	vibLayout.addWidget(&vibDepthLabel, 2, 0, 1, 1, Qt::AlignHCenter);
	vibLayout.addWidget(&vibPeriodSelect, 1, 1);
	vibLayout.addWidget(&vibPeriodLabel, 2, 1, 1, 1, Qt::AlignHCenter);

	layout.addWidget(&waveformSelect);
	layout.addWidget(&transposeSelect);
	layout.addWidget(&envelope);
	layout.addWidget(&vibratoSection);
	layout.addWidget(&levelSelect);
	layout.addWidget(&fmDepthSelect);

	mainArea.setLayout(&layout);
	envelope.setLayout(&envLayout);
	vibratoSection.setLayout(&vibLayout);
	setCentralWidget(&mainArea);

	show();
	setFocus();

	QObject::connect(&waveformSelect, SIGNAL(activated(int)), this, SLOT(changeWaveform(int)));
	QObject::connect(&waveformSelect, SIGNAL(activated(int)), this, SLOT(setFocus()));

	QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), this, SLOT(setTranspose(int)));
	QObject::connect(&transposeSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&attackSelect, SIGNAL(valueChanged(int)), this, SLOT(setAttack(int)));
	QObject::connect(&attackSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&decaySelect, SIGNAL(valueChanged(int)), this, SLOT(setDecay(int)));
	QObject::connect(&decaySelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&sustainSelect, SIGNAL(valueChanged(int)), this, SLOT(setSustain(int)));
	QObject::connect(&sustainSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&releaseSelect, SIGNAL(valueChanged(int)), this, SLOT(setRelease(int)));
	QObject::connect(&releaseSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&vibDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setVibDepth(int)));
	QObject::connect(&vibDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&vibPeriodSelect, SIGNAL(valueChanged(int)), this, SLOT(setVibPeriod(int)));
	QObject::connect(&vibPeriodSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&levelSelect, SIGNAL(valueChanged(int)), this, SLOT(setLevel(int)));
	QObject::connect(&levelSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));

	QObject::connect(&fmDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFmDepth(int)));
	QObject::connect(&fmDepthSelect, SIGNAL(valueChanged(int)), this, SLOT(setFocus()));
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
			keyboard->setTransposeInKey(key - Qt::Key_1);
		else
			keyboard->setOctave(key - Qt::Key_1 - 4);
	}
	else if(!event->isAutoRepeat() && keyMap.find(key) != keyMap.end()) {
		keyboard->playNote(keyMap[key]);
	}
	else
		event->ignore();
}

void Synthesizer::keyReleaseEvent(QKeyEvent *event) {
	setFocus();
	if(!event->isAutoRepeat() && keyMap.find(event->key()) != keyMap.end()) {
		keyboard->releaseNote(keyMap[event->key()]);
	}
	else
		event->ignore();
}

void Synthesizer::done() {
	state = QUITTING;
}

void Synthesizer::changeWaveform(int i) {
	keyboard->setWaveform(i);
}

void Synthesizer::setTranspose(int i) {
	keyboard->setTranspose(i);
}

void Synthesizer::setAttack(int i) {
	keyboard->setAttack(((double)i)/50);
}

void Synthesizer::setDecay(int i) {
	keyboard->setDecay(((double)i)/50);
}

void Synthesizer::setRelease(int i) {
	keyboard->setRelease(((double)i)/50);
}

void Synthesizer::setSustain(int i) {
	keyboard->setSustain(((double)i)/100);
}

void Synthesizer::setLevel(int i) {
	keyboard->setLevel(((double)i)/1000);
}

void Synthesizer::setFmDepth(int i) {
	keyboard->setFmDepth(((double)i)*100);
}

void Synthesizer::setVibDepth(int value) {
	vibrato.setDepth(value*100);
}

void Synthesizer::setVibPeriod(int value) {
	vibrato.setPeriod(((double)value)/100);
}

void Synthesizer::configureSoundDevice() {
	unsigned int val;
	int rc;
	snd_pcm_hw_params_t *params;
	snd_pcm_sw_params_t *sw_params;
	snd_pcm_uframes_t hw_buffer;

	frames = 32;
	hw_buffer = frames*16;
	val = SAMPLE_RATE;

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
	snd_pcm_hw_params_set_rate_near(handle, params, &val, 0);
	rc = snd_pcm_hw_params_set_buffer_size_near(handle, params, &hw_buffer);
    if (rc < 0) {
        fprintf(stderr, "unable to set buffer: %s\n", snd_strerror(rc));
        exit(1);
	}
    hw_buffer /= 2;
    rc = snd_pcm_hw_params_set_period_size_near(handle, params, &frames, 0);
    if (rc < 0) {
        fprintf(stderr, "unable to set period_size: %s\n", snd_strerror(rc));
        exit(1);
	}
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
        exit(1);
	}
	snd_pcm_sw_params_alloca(&sw_params);
    rc = snd_pcm_sw_params_set_start_threshold(handle, sw_params, hw_buffer-frames);
	if (rc < 0) {
		fprintf(stderr, "unable to set start threshold: %s\n", snd_strerror(rc));
		exit(1);
	}
    rc = snd_pcm_sw_params_set_avail_min(handle, sw_params, 4);
	if (rc < 0) {
		fprintf(stderr, "unable to set avail min: %s\n", snd_strerror(rc));
		exit(1);
	}
	rc = snd_pcm_sw_params(handle, sw_params);
	if (rc < 0) {
		fprintf(stderr, "unable to set sw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}
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
	return keyboard->getWaveforms();
}

Synthesizer::~Synthesizer() {
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
}
