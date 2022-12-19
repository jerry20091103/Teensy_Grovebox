#include "AudioFX.h"

AudioFX_ AudioFX;

FXFreeverbs::FXFreeverbs()
{
    //reverb = &freeverbs1;
    lpf[0] = &freeverbBiquadL;
    lpf[1] = &freeverbBiquadR;
    mix[0] = &freeverbMixerL;
    mix[1] = &freeverbMixerR;

    // set default value
    setRoomSize(0.5);
    setDamping(0.5);
    setLpf(10000);
    setMix(0.5);
}

void FXFreeverbs::setMix(float value)
{
    mix[0]->gain(0, 1 - value);
    mix[1]->gain(0, 1 - value);
    mix[0]->gain(1, value);
    mix[1]->gain(1, value);
}

void FXFreeverbs::setRoomSize(float value)
{
    //reverb->roomsize(value);
}

void FXFreeverbs::setDamping(float value)
{
    //reverb->damping(value);
}

void FXFreeverbs::setLpf(float frequecny)
{
    lpf[0]->setLowpass(0, frequecny);
    lpf[1]->setLowpass(0, frequecny);
}

void FXFreeverbs::setWithMem(FXFreeverb_Mem *mem)
{
    if(mem != nullptr)
    {
        setRoomSize(mem->roomSize);
        setDamping(mem->damping);
        setLpf(mem->lpf);
        setMix(mem->mix);
    }
}

AudioFX_::AudioFX_(/* args */)
{
}