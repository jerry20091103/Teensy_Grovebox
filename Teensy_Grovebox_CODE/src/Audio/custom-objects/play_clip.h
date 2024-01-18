#ifndef PLAY_CLIP_H
#define PLAY_CLIP_H
#include "Audio.h"
#include "../AudioUtility.h"
#include "Utility/SerialPrint.h"

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

        if (!isPlaying)
            return;

        audio_block_t *block;
        block = allocate();
        if (block == NULL)
            return;

        if (speed == 1.0f)
        {
            if (isLoop && crossFade != 0 && currentBlock >= loopEndPoint - crossFadeLength)
            {
                // apply crosfade looping
                float frac = (loopEndPoint - currentBlock) / (float)crossFadeLength;
                int currentFade = currentBlock - crossFadeLength;
                if (currentFade < 0)
                {
                    currentFade = 0;
                    serialPrintln("ERROR: AudioPlayClip::update(), currentFade < 0");
                }
                for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
                {
                    block->data[i] = ((1.0f - frac) * ((int16_t *)clip)[(int)currentBlock * AUDIO_BLOCK_SAMPLES + i] + frac * ((int16_t *)clip)[(int)currentFade * AUDIO_BLOCK_SAMPLES + i]);
                }
            }
            else
            {
                // copy data and send to output
                memcpy(block->data, &clip[(int)currentBlock], sizeof(audio_block_data_t));
            }
            // update playing position
            currentBlock++;
        }
        else
        {
            if (isLoop && crossFade != 0 && currentBlock >= loopEndPoint - crossFadeLength)
            {
                // apply crosfade looping
                float fadeFrac = (loopEndPoint - currentBlock) / (float)crossFadeLength;
                int currentFade = currentBlock - crossFadeLength;
                if (currentFade < 0)
                {
                    currentFade = 0;
                    serialPrintln("ERROR: AudioPlayClip::update(), currentFade < 0");
                }
                // interpolate data with crossfade
                for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
                {
                    float pos = currentBlock * AUDIO_BLOCK_SAMPLES + (float)i * speed;
                    int posPrev = (int)pos;
                    int posNext = posPrev + 1;
                    float frac = pos - posPrev;
                    float posFade = currentFade * AUDIO_BLOCK_SAMPLES + (float)i * speed;
                    int posPrevFade = (int)posFade;
                    int posNextFade = posPrevFade + 1;
                    int16_t currentSample = ((1.0f - frac) * ((int16_t *)clip)[posPrev] + frac * ((int16_t *)clip)[posNext]);
                    int16_t fadeSample = ((1.0f - frac) * ((int16_t *)clip)[posPrevFade] + frac * ((int16_t *)clip)[posNextFade]);
                    block->data[i] = fadeFrac * currentSample + (1.0f - fadeFrac) * fadeSample;
                }
            }
            // interpolate data and send to output
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
            {
                float pos = currentBlock * AUDIO_BLOCK_SAMPLES + (float)i * speed;
                int posPrev = (int)pos;
                int posNext = posPrev + 1;
                float frac = pos - posPrev;
                block->data[i] = ((1.0f - frac) * ((int16_t *)clip)[posPrev] + frac * ((int16_t *)clip)[posNext]);
            }
            // update playing position
            currentBlock += speed;
        }
        transmit(block);
        // check loop and end points
        if (isLoop && noteOn)
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
            serialPrintln("ERROR: AudioPlayClip::play(), clip is NULL");
            return;
        }
        __disable_irq();
        isPlaying = true;
        noteOn = true;
        currentBlock = startPoint;
        __enable_irq();
    }
    // stop playing immediately
    void stop(void)
    {
        __disable_irq();
        isPlaying = false;
        noteOn = false;
        __enable_irq();
    }
    // stop looping and play to the end of the clip
    void noteOff()
    {
        __disable_irq();
        noteOn = false;
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
        crossFadeLength = (loopEndPoint - loopStartPoint) * crossFade;
        __enable_irq();
    }
    // Sets the loop stop position. 0 and 1 represents the start and end of a clip
    void setLoopEndPoint(float position)
    {
        uint16_t pos = calClipPosition(position);
        __disable_irq()
            loopEndPoint = pos;
        crossFadeLength = (loopEndPoint - loopStartPoint) * crossFade;
        __enable_irq();
    }
    // Enable or disable looping.
    void loop(bool enable)
    {
        __disable_irq()
            isLoop = enable;
        __enable_irq()
    }
    // Returns whether the clip is playing.
    bool playing()
    {
        bool ret;
        __disable_irq()
            ret = isPlaying;
        __enable_irq() return ret;
    }
    // Returns the current position in the clip. Position is between 0 and 1. 0 and 1 represents the start and end of a clip
    float getCurrentPosition()
    {
        float ret;
        __disable_irq()
            ret = (float)currentBlock / (float)clipLength;
        __enable_irq() return ret;
    }
    // Sets the playback speed. 1.0 is normal speed, 0.5 is half speed, 2.0 is double speed...etc.
    void setSpeed(float speed)
    {
        __disable_irq() this->speed = speed;
        __enable_irq();
    }
    // Sets the ratio of crossfade when looping. 0.0 is no crossfade, 1.0 means the entire loop duration is crossfaded.
    void setLoopCrossFade(float ratio)
    {
        __disable_irq()
            crossFade = ratio;
        crossFadeLength = (loopEndPoint - loopStartPoint) * crossFade;
        __enable_irq();
    }

private:
    uint16_t calClipPosition(float position)
    {
        return clipLength * constrain(position, 0.0f, 1.0f);
    }
    audio_block_t *inputQueueArray[1];
    audio_block_data_t *clip;
    float speed = 1.0f;
    float currentBlock = 0.0f;
    float crossFade = 0.0f;
    uint16_t startPoint = 0;
    uint16_t endPoint = 0;
    uint16_t loopStartPoint = 0;
    uint16_t loopEndPoint = 0;
    uint16_t clipLength = 0;
    uint16_t limit = 0;
    uint16_t crossFadeLength = 0;
    bool isLoop = false;
    bool isPlaying = false;
    bool noteOn = false;
};
#endif // PLAY_CLIP_H