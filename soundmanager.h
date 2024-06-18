#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <AudioToolbox/AudioToolbox.h>

constexpr int kFramesPerBuffer = 1 << 9;  // Adjust buffer size as needed
constexpr int kBitsPerChannel = 16;
constexpr int kChannelsPerFrame = 2;
constexpr int kBytesPerFrame = kChannelsPerFrame * kBitsPerChannel / 8;

class SoundManager {
public:
  SoundManager();
  ~SoundManager();
  void writeSample(int sample);

private:
  static void AudioQueueCallback(void *custom_data, AudioQueueRef queue,
                                 AudioQueueBufferRef buffer);

  AudioQueueRef audio_queue_;
  struct AudioBuffer {
    AudioBuffer() : buffer() {}
    AudioQueueBufferRef buffer_ref;
    char buffer[kFramesPerBuffer * kBytesPerFrame];
    int frame_index = 0;
  };
  AudioBuffer buffer_[2];
  int current_buffer_ = 0;
  int frames_per_buffer_;
  bool is_shut_down_ = false;
};

#endif // SOUNDMANAGER_H
