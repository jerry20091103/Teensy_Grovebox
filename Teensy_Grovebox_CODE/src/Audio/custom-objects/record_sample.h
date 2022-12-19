#ifndef RECORD_SAMPLE_H
#define RECORD_SAMPLE_H
#include "Audio.h"

// Get the middle sample in the current audio block.

class AudioRecordSample : public AudioStream
{
public:
    AudioRecordSample() : AudioStream(1, inputQueueArray)
    {
        isAvailable = false;
        sample = 0;
    }
    virtual void update(void)
    {
        audio_block_t *block;
        block = receiveReadOnly(0);
        if (block)
        {
            sample = block->data[AUDIO_BLOCK_SAMPLES / 2];
            isAvailable = true;
            release(block);
        }
    }
    // returns whether a new sample is available
    bool available(void)
    {
        bool ret;
        __disable_irq();
        ret = isAvailable;
        __enable_irq();
        return ret;
    }
    // returns a sample. If not available, returns the old value.
    int16_t readSample(void)
    {
        int16_t ret = 0;
        __disable_irq();
        if (isAvailable)
        {
            isAvailable = false;
        }
        ret = sample;
        __enable_irq();
        return ret;
    }

private:
    audio_block_t *inputQueueArray[1];
    bool isAvailable;
    int16_t sample;
};

#endif // RECORD_SAMPLE_H