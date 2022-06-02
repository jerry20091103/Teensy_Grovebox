#ifndef AUDIO_FX_H
#define AUDIO_FX_H

#include "AudioObjects.h"

#define FLANGE_BUF_SIZE 20 * AUDIO_BLOCK_SAMPLES

// FX___ classes wraps teensy audio effect objects, and provide dry/wet mix and useful functions
// class FXFlange
// {
// private:
// public : FXFlange();
//     // set dry/wet signal ratio (0~1)
//     void setMix(float value);
// };

// class FXDelay
// {
// private:
// public:
//     FXDelay();
// };

// ___Mem are memory structs to store in each pages (pages take care of paramenter storing, not the effect itself.)
struct FXFreeverb_Mem
{
    float mix = 0.2;
    float roomSize = 0.5;
    float damping = 0.5;
    float lpf = 10000;
};

class FXFreeverbs
{
private:
    AudioEffectFreeverbStereo *reverb;
    AudioFilterBiquad *lpf[2];
    AudioMixer4 *mix[2];
public:
    FXFreeverbs();
    // set dry/wet signal ratio (0~1)
    void setMix(float value);
    void setRoomSize(float value);
    void setDamping(float value);
    void setLpf(float frequecny);
    void setWithMem(FXFreeverb_Mem *mem);
};


// AudioFX class wraps the whole FX module that includes all other effects.
class AudioFX_
{
private:
    
public:
    AudioFX_(/* args */);
    FXFreeverbs reverb;
};

extern AudioFX_ AudioFX;
#endif