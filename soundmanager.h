#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#define SAMPLE_RATE 44100.0

#include <AudioToolbox/AudioToolbox.h>
#include "soundprocessor.h"


class SoundManager {
  public:
    SoundManager();
    ~SoundManager();
    void writeSample(int sample);
  private:
    void configureSoundDevice();
    static void AudioQueueCallback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer);

    AudioQueueRef queue;
    static const int kNumberBuffers = 3;
    AudioQueueBufferRef buffers[kNumberBuffers];
    int bufferIndex;
    char *buffer;
    int frames;
    int lastSample;
};


#endif
