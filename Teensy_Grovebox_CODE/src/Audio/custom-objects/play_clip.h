#ifndef PLAY_CLIP_H
#define PLAY_CLIP_H
#include "Audio.h"
#include "../AudioUtility.h"

// Play an audio clip from EXTMEM, recorded with AudioRecordClip
// Has start/stop and looping functionality

class AudioPlayClip : public AudioStream
{
public:
    AudioPlayClip() : AudioStream(0, NULL)
    {
        // any extra initialization
    }
    virtual void update(void)
    {
        if (clip == NULL)
            return;
        // play the clip from EXTMEM
        if (isPlaying)
        {
            audio_block_t *block;
            block = allocate();
            if (block == NULL)
                return;
            // copy data and send to output
            memcpy(block->data, &clip[currentBlock], sizeof(audio_block_data_t));
            transmit(block);
            // update playing position
            currentBlock++;
            if (isLoop)
            {
                if (currentBlock >= loopEndPoint)
                    currentBlock = loopStartPoint;
            }
            else
            {
                if (currentBlock >= endPoint || currentBlock >= limit)
                {
                    currentBlock = startPoint;
                    isPlaying = false;
                }
            }

            release(block);
        }
    }

    void setClip(audio_block_data_t *clip, uint16_t length)
    {
        __disable_irq();
        this->clip = clip;
        this->clipLength = length;
        currentBlock = 0;
        endPoint = length;
        limit = length;
        __enable_irq();
    }
    void play(void)
    {
        if (clip == NULL)
        {
            Serial.println("ERROR: AudioPlayClip::play(), clip is NULL");
            return;
        }
        __disable_irq();
        isPlaying = true;
        currentBlock = clipLength * startPoint;
        __enable_irq();
    }
    void stop(void)
    {
        __disable_irq();
        isPlaying = false;
        __enable_irq();
    }
    // Sets the start position. 0 and 1 represents the start and end of a clip
    void setStartPoint(float position)
    {
        uint16_t pos = calClipPosition(position);
        __disable_irq()
        startPoint = pos;
        __enable_irq();
    }
    // Sets the stop position. 0 and 1 represents the start and end of a clip
    void setEndPoint(float position)
    {
        uint16_t pos = calClipPosition(position);
        __disable_irq()
        endPoint = pos;
        __enable_irq();
    }
    // Sets the loop start position. 0 and 1 represents the start and end of a clip
    void setLoopStartPoint(float position)
    {
        uint16_t pos = calClipPosition(position);
        __disable_irq()
        loopStartPoint = pos;
        __enable_irq();
    }
    // Sets the loop stop position. 0 and 1 represents the start and end of a clip
    void setLoopEndPoint(float position)
    {
        uint16_t pos = calClipPosition(position);
        __disable_irq()
        loopEndPoint = pos;
        __enable_irq();
    }
    
    void loop(bool enable)
    {
        __disable_irq()
        isLoop = enable;
        __enable_irq()
    }

private:
    uint16_t calClipPosition(float position)
    {
        return clipLength * constrain(position, 0.0f, 1.0f);
    }
    audio_block_t *inputQueueArray[1];
    audio_block_data_t *clip;
    uint16_t startPoint = 0;
    uint16_t endPoint = 0;
    uint16_t loopStartPoint = 0;
    uint16_t loopEndPoint = 1;
    uint16_t clipLength = 0;
    uint16_t currentBlock = 0;
    uint16_t limit = 0;
    bool isLoop = false;
    bool isPlaying = false;
};
#endif // PLAY_CLIP_H