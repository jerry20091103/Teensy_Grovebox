#ifndef SYNTH_MOD_PARAM_H
#define SYNTH_MOD_PARAM_H

#include "Audio/AudioVoice.h"

/*
    An abstract class for a parameter that can be modulated in the synth.
    *All parameter values are between 0.0f and 1.0f unless otherwise specified*
    *Modulation amounts are between -1.0f and 1.0f*
*/
class SynthModParam
{
public:
    SynthModParam(AudioVoice *voiceArr) : voiceArr(voiceArr) {}
    // modulates the parameter for a specific voice. amount is a value between -1.0f and 1.0f
    virtual void modulate(uint8_t voiceId, float amount) = 0;
    // resets the modulation of the parameter for all voices
    virtual void resetModulation() final;
    // sets the value of the parameter for all voices (0.0f to 1.0f)
    virtual void set(float value) final;
    // gets the value of the parameter
    virtual float get() final;

protected:
    // sets the value of the parameter for a specific voice (0.0f to 1.0f)
    virtual void setVoice(uint8_t voiceId, float value) = 0;
    float value = 0.0f;
    AudioVoice *voiceArr = nullptr;
};

/*
    An abstract class for SynthModparams that needs an instace id.
    Example: There are 2 OSCs, each with a pitch offset and a level.
*/
class SynthModParamWithId : public SynthModParam
{
public:
    SynthModParamWithId(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParam(voiceArr), instanceId(instanceId) {}
    virtual void setVoice(uint8_t voiceId, float value) = 0;
    virtual void modulate(uint8_t voiceId, float amount) = 0;

protected:
    uint8_t instanceId = 0;
};

/*
    A child class of SynthModParamWithId.
    This class is for the pitch offset of an oscillator.
*/
class OscPitchOffset : public SynthModParamWithId
{
public:
    OscPitchOffset(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value_signed) override;
    void modulate(uint8_t voiceId, float amount) override;
    float getModValue(uint8_t voiceId);
private:
    float modValue[MAX_VOICE] = {0.0f};
};

/*
    A child class of SynthModParamWithId.
    This class is for the level of an oscillator.
*/
class OscLevel : public SynthModParamWithId
{
public:
    OscLevel(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of SynthModParamWithId.
    This class is for the PWM of an oscillator square wave.
*/
class OscPwm : public SynthModParamWithId
{
public:
    OscPwm(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of SynthModParam.
    This class is for the level of the noise generator.
*/
class NoiseLevel : public SynthModParam
{
public:
    NoiseLevel(AudioVoice *voiceArr) : SynthModParam(voiceArr) {}
    void setVoice(uint8_t voiceId, float value) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of SynthModParam.
    This class is for the cutoff frequency of the filter.
*/ 
class FilterCutoff : public SynthModParam
{
public:
    FilterCutoff(AudioVoice *voiceArr) : SynthModParam(voiceArr) {}
    void setVoice(uint8_t voiceId, float value_hz) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of SynthModParam.
    This class is for the resonance of the filter.
*/
class FilterResonance : public SynthModParam
{
public:
    FilterResonance(AudioVoice *voiceArr) : SynthModParam(voiceArr) {}
    void setVoice(uint8_t voiceId, float value) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of SynthModParamWithId.
    This class is for the frequency of the LFO.
*/
class LfoFreq : public SynthModParamWithId
{
public:
    LfoFreq(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value_hz) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of SynthModParamWithId.
    This class is for the level of the LFO.
*/
class LfoLevel : public SynthModParamWithId
{
public:
    LfoLevel(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    An abstract class for SynthModParamsWithId that are envelope parameters.
    Why: Envelope parameters share the same modulation method.
*/
class EnvParam : public SynthModParamWithId
{
public:
    EnvParam(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of EnvParam.
    This class is for the Delay of an envelope.
*/
class EnvDelay : public EnvParam
{
public:
    EnvDelay(AudioVoice *voiceArr, uint8_t instanceId) : EnvParam(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value_ms) override;
};

/*
    A child class of EnvParam.
    This class is for the Attack of an envelope.
*/
class EnvAttack : public EnvParam
{
public:
    EnvAttack(AudioVoice *voiceArr, uint8_t instanceId) : EnvParam(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value_ms) override;
};

/*
    A child class of EnvParam.
    This class is for the Decay of an envelope.
*/
class EnvDecay : public EnvParam
{
public:
    EnvDecay(AudioVoice *voiceArr, uint8_t instanceId) : EnvParam(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value_ms) override;
};

/*
    A child class of SynthModParamWithId.
    Sustain is a special case, because it is not a time value. So it is not a child of EnvParam.
    This class is for the Sustain of an envelope.
*/
class EnvSustain : public SynthModParamWithId
{
public:
    EnvSustain(AudioVoice *voiceArr, uint8_t instanceId) : SynthModParamWithId(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value) override;
    void modulate(uint8_t voiceId, float amount) override;
};

/*
    A child class of EnvParam.
    This class is for the Release of an envelope.
*/
class EnvRelease : public EnvParam
{
public:
    EnvRelease(AudioVoice *voiceArr, uint8_t instanceId) : EnvParam(voiceArr, instanceId) {}
    void setVoice(uint8_t voiceId, float value_ms) override;
};


#endif