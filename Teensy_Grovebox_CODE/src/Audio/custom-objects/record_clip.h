#ifndef RECORD_CLIP_H
#define RECORD_CLIP_H
#include "Audio.h"
#include "../AudioUtility.h"

// Record an audio clip into to EXTMEM

#define AUDIO_RECORD_CLIP_MAX_LENGTH 2200 // about 6 seconds of audio

class AudioRecordClip : public AudioStream
{
public:
    AudioRecordClip() : AudioStream(1, inputQueueArray)
    {
        // allocate space in external RAM (EXTMEM)
        clip = (audio_block_data_t*) extmem_malloc(AUDIO_RECORD_CLIP_MAX_LENGTH * sizeof(audio_block_data_t));
        if (clip == NULL)
        {
            Serial.println("ERROR: AudioRecordClip::AudioRecordClip(), could not allocate memory for clip");
        }
    }
    virtual void update(void)
    {
        // record incoming audio data into EXTMEM
        if (isRecording)
        {
            audio_block_t *block;
            block = receiveReadOnly(0);
            if (block)
            {
                if (currentBlock < AUDIO_RECORD_CLIP_MAX_LENGTH)
                {
                    // copy the audio block into the clip
                    memcpy(&clip[currentBlock], block->data, sizeof(audio_block_data_t));
                    currentBlock++;
                }
                release(block);
            }
        }
    }
    // returns location of the recorded clip
    audio_block_data_t *getClip(void)
    {
        return clip;
    }
    // returns length of the recorded clip
    uint16_t getClipLength(void)
    {
        uint16_t ret;
        __disable_irq();
        ret = clipLength;
        __enable_irq();
        return ret;
    }
    void startRecording(void)
    {
        __disable_irq();
        isRecording = true;
        currentBlock = 0;
        __enable_irq();
    }
    void stopRecording(void)
    {
        __disable_irq();
        isRecording = false;
        clipLength = currentBlock;
        __enable_irq();
    }


private:
    audio_block_t *inputQueueArray[1];
    audio_block_data_t *clip;
    uint16_t clipLength = 0;
    uint16_t currentBlock = 0;
    bool isRecording = false;
};

#endif // RECORD_CLIP_H