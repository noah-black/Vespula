#include "soundmanager.h"
#include <cmath>
#include <iostream>

SoundManager::SoundManager() {
  AudioStreamBasicDescription format;
  memset(&format, 0, sizeof(format));
  format.mSampleRate = 44100; // Use the determined sample rate
  format.mFormatID = kAudioFormatLinearPCM;
  format.mFormatFlags =
      kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
  format.mBitsPerChannel = kBitsPerChannel;
  format.mChannelsPerFrame = kChannelsPerFrame;
  format.mBytesPerFrame = kBytesPerFrame;
  format.mFramesPerPacket = 1;
  format.mBytesPerPacket = kBytesPerFrame;

  OSStatus status = AudioQueueNewOutput(&format, AudioQueueCallback, this,
                                        nullptr, nullptr, 0, &audio_queue_);
  if (status != noErr) {
    std::cerr << "AudioQueueNewOutput error: " << status << std::endl;
    exit(1);
  }

  for (int i = 0; i < 2; ++i) {
    status = AudioQueueAllocateBuffer(
        audio_queue_, kFramesPerBuffer * kBytesPerFrame, &buffer_[i].buffer_ref);
    if (status != noErr) {
      std::cerr << "AudioQueueAllocateBuffer error: " << status << std::endl;
      exit(1);
    }
    buffer_[i].buffer_ref->mAudioDataByteSize = kFramesPerBuffer * kBytesPerFrame;
    current_buffer_ = i;
    AudioQueueCallback(this, audio_queue_,
                       buffer_[i].buffer_ref); // Pre-fill the buffer
  }

  AudioQueueStart(audio_queue_, nullptr);
}

void SoundManager::AudioQueueCallback(void *custom_data, AudioQueueRef queue,
                                      AudioQueueBufferRef buffer) {
  SoundManager *self = static_cast<SoundManager *>(custom_data);
  int current_buffer = self->current_buffer_;
  memcpy(buffer->mAudioData, self->buffer_[current_buffer].buffer, kFramesPerBuffer * kBytesPerFrame);
  OSStatus status = AudioQueueEnqueueBuffer(queue, buffer, 0, nullptr);
  self->buffer_[current_buffer].frame_index = 0;
  if (status != noErr) {
    std::cerr << "AudioQueueEnqueueBuffer error: " << status << std::endl;
  }
}

void SoundManager::writeSample(int sample) {
  AudioBuffer& buffer = buffer_[current_buffer_];
  while (buffer.frame_index >= kFramesPerBuffer && !is_shut_down_) {}
  sample = std::max(-32768, std::min(32767, sample)); // Prevent clipping
  buffer.buffer[buffer.frame_index * 4] = sample & 255;
  buffer.buffer[buffer.frame_index * 4 + 1] = (sample >> 8) & 255;
  buffer.buffer[buffer.frame_index * 4 + 2] = sample & 255;
  buffer.buffer[buffer.frame_index * 4 + 3] = (sample >> 8) & 255;
  buffer.frame_index++;

  if (buffer.frame_index >= kFramesPerBuffer) {
    current_buffer_ = (current_buffer_ + 1) % 2;
  }
}

SoundManager::~SoundManager() {
  AudioQueueStop(audio_queue_, true);
  AudioQueueDispose(audio_queue_, true);
  is_shut_down_ = true;
}
