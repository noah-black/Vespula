#include "soundmanager.h"

SoundManager::SoundManager() {
	configureSoundDevice();
	buffer = new char[frames*4];
    bufferIndex = 0;
    counter = 0;
}
void SoundManager::writeSample(int sample) {
    counter++;
	int rc = frames;
    sample = sample > CEILING ? CEILING : sample;
    sample = sample < -CEILING ? -CEILING : sample;
	buffer[bufferIndex * 4] = sample & 255;
	buffer[(bufferIndex * 4) + 2] = sample & 255;
	buffer[(bufferIndex * 4) + 1] = sample >> 8;
	buffer[(bufferIndex * 4) + 3] = sample >> 8;
    bufferIndex++;
    if(bufferIndex == frames) {
        rc = snd_pcm_writei(handle, buffer, frames);
		while(rc == -EPIPE) {
            rc = snd_pcm_recover(handle, rc, 1);
            printf("underrun\n");
            if(rc != 0) {
			    fprintf(stderr, "Could not recover from underrun!\n");
                exit(1);
            }
            rc = snd_pcm_writei(handle, buffer, frames);
        }
		if (rc < 0) 
			printf("error from writei: %s\n", snd_strerror(rc));
		else if (rc != frames) 
			printf("short write, write %d frames\n", rc);
        bufferIndex = 0;
	}
}

void SoundManager::configureSoundDevice() {
	unsigned int val;
	int rc;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_sw_params_t *sw_params;

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
	snd_pcm_hw_params_alloca(&hw_params);
	snd_pcm_hw_params_any(handle, hw_params);
	snd_pcm_hw_params_set_access(handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(handle, hw_params, SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(handle, hw_params, 2);
	snd_pcm_hw_params_set_rate_near(handle, hw_params, &val, 0);
	rc = snd_pcm_hw_params_set_buffer_size_near(handle, hw_params, &hw_buffer);
    if (rc < 0) {
        fprintf(stderr, "unable to set buffer: %s\n", snd_strerror(rc));
        exit(1);
	}
    hw_buffer /= 2;
    rc = snd_pcm_hw_params_set_period_size_near(handle, hw_params, &frames, 0);
    if (rc < 0) {
        fprintf(stderr, "unable to set period_size: %s\n", snd_strerror(rc));
        exit(1);
	}
    rc = snd_pcm_hw_params(handle, hw_params);
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
	if (rc < 0) {
		fprintf(stderr, "unable to set sw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}
}

SoundManager::~SoundManager() {
    delete[] buffer;
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
}
