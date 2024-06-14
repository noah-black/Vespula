#include "soundmanager.h"
#include <AudioToolbox/AudioToolbox.h>

static const int kNumberBuffers = 3;
static const int kBufferSize = 1024;

SoundManager::SoundManager() {
    configureSoundDevice();
    buffer = new char[kBufferSize];
    bufferIndex = 0;
}

void SoundManager::writeSample(int sample) {
    lastSample = sample;
    sample = sample > CEILING ? CEILING : sample;
    sample = sample < -CEILING ? -CEILING : sample;

    buffer[bufferIndex * 4] = sample & 255;
    buffer[(bufferIndex * 4) + 2] = sample & 255;
    buffer[(bufferIndex * 4) + 1] = sample >> 8;
    buffer[(bufferIndex * 4) + 3] = sample >> 8;

    bufferIndex++;
    if(bufferIndex == frames) {
        // Enqueue buffer for playback
        AudioQueueBufferRef audioBuffer = buffers[bufferIndex % kNumberBuffers];
        memcpy(audioBuffer->mAudioData, buffer, kBufferSize);
        audioBuffer->mAudioDataByteSize = kBufferSize;
        AudioQueueEnqueueBuffer(queue, audioBuffer, 0, NULL);
        bufferIndex = 0;
    }
}

void SoundManager::configureSoundDevice() {
    AudioStreamBasicDescription format;
    memset(&format, 0, sizeof(format));
    format.mSampleRate = SAMPLE_RATE;
    format.mFormatID = kAudioFormatLinearPCM;
    format.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    format.mFramesPerPacket = 1;
    format.mChannelsPerFrame = 2;
    format.mBitsPerChannel = 16;
    format.mBytesPerPacket = 4;
    format.mBytesPerFrame = 4;

    OSStatus status = AudioQueueNewOutput(&format, AudioQueueCallback, this, NULL, kCFRunLoopCommonModes, 0, &queue);
    if(status != noErr) {
        fprintf(stderr, "Error initializing Audio Queue: %d\n", status);
        exit(1);
    }

    frames = kBufferSize / format.mBytesPerFrame;
    for(int i = 0; i < kNumberBuffers; ++i) {
        status = AudioQueueAllocateBuffer(queue, kBufferSize, &buffers[i]);
        if(status != noErr) {
            fprintf(stderr, "Error allocating buffer: %d\n", status);
            exit(1);
        }
        buffers[i]->mAudioDataByteSize = kBufferSize;
        memset(buffers[i]->mAudioData, 0, kBufferSize);
        AudioQueueEnqueueBuffer(queue, buffers[i], 0, NULL);
    }

    status = AudioQueueStart(queue, NULL);
    if(status != noErr) {
        fprintf(stderr, "Error starting Audio Queue: %d\n", status);
        exit(1);
    }
}

void SoundManager::AudioQueueCallback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer) {
    // This function will be called when an audio buffer has finished playing
    SoundManager *soundManager = static_cast<SoundManager *>(custom_data);
    memset(buffer->mAudioData, 0, buffer->mAudioDataByteSize); // Clear the buffer
    AudioQueueEnqueueBuffer(queue, buffer, 0, NULL); // Re-enqueue the buffer for continuous playback
}

SoundManager::~SoundManager() {
    AudioQueueStop(queue, true);
    AudioQueueDispose(queue, true);
    delete[] buffer;
}
