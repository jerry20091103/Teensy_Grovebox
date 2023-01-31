#include "Audio/SynthModParam.h"
#include "SynthModParam.h"

void SynthModParam::resetModulation()
{
    for (uint8_t voiceId = 0; voiceId < MAX_VOICE; voiceId++)
    {
        modulate(voiceId, 0.0f);
    }
}

void SynthModParam::set(float value)
{
    this->value = value;
    for (uint8_t voiceId = 0; voiceId < MAX_VOICE; voiceId++)
    {
        setVoice(voiceId, value);
    }
}

float SynthModParam::get()
{
    return value;
}

// value is between -1.0f and 1.0f
void OscPitchOffset::setVoice(uint8_t voiceId, float value_signed)
{
    // get current frequency
    float freq = voiceArr[voiceId].frequency;
    // offest the current pitch by the value, the range is 4 octaves
    voiceArr[voiceId].setOscFreq(instanceId, freq * powf(2, value_signed * 4.0f) * voiceArr[voiceId].curPitchBendMult);
    // todo: ugly?
}

void OscPitchOffset::modulate(uint8_t voiceId, float amount)
{
    modValue[voiceId] = amount;
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, -1.0f, 1.0f));
}

// This is a hack to get current modulation value for ptich offset, for pitchbend reasons...
float OscPitchOffset::getModValue(uint8_t voiceId)
{
    return modValue[voiceId];
}

void OscLevel::setVoice(uint8_t voiceId, float value)
{
    // 0~1
    voiceArr[voiceId].waveform[instanceId]->amplitude(value);
}

void OscLevel::modulate(uint8_t voiceId, float amount)
{
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, 0.0f, 1.0f));
}

void OscPwm::setVoice(uint8_t voiceId, float value)
{
    // 0~1
    voiceArr[voiceId].waveform[instanceId]->pulseWidth(value);
}

void OscPwm::modulate(uint8_t voiceId, float amount)
{
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, 0.0f, 1.0f));
}

void NoiseLevel::setVoice(uint8_t voiceId, float value)
{
    // 0~1
    voiceArr[voiceId].noise->amplitude(value);
}

void NoiseLevel::modulate(uint8_t voiceId, float amount)
{
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, 0.0f, 1.0f));
}

// value is in HZ
void FilterCutoff::setVoice(uint8_t voiceId, float value_hz)
{
    // frequency in HZ
    voiceArr[voiceId].ladderFilter->frequency(value_hz);
}

void FilterCutoff::modulate(uint8_t voiceId, float amount)
{
    // mod = original value (Hz) * 10^(amount * 3)
    setVoice(voiceId, constrain(value * powf(10, amount * 3.0f), 20.0f, 20000.0f));
}

void FilterResonance::setVoice(uint8_t voiceId, float value)
{
    // 0~1
    voiceArr[voiceId].ladderFilter->resonance(value);
}

void FilterResonance::modulate(uint8_t voiceId, float amount)
{
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, 0.0f, 1.0f));
}

void LfoFreq::setVoice(uint8_t voiceId, float value_hz)
{
    // frequency in HZ
    voiceArr[voiceId].lfo[instanceId]->frequency(value_hz);
}

void LfoFreq::modulate(uint8_t voiceId, float amount)
{
    // mod = original value (Hz) * 2^(amount * 7)
    setVoice(voiceId, constrain(value * powf(2, amount * 7.0f), 0.0f, 128.0f));
}

void LfoLevel::setVoice(uint8_t voiceId, float value)
{
    // 0~1
    voiceArr[voiceId].lfo[instanceId]->amplitude(value);
}

void LfoLevel::modulate(uint8_t voiceId, float amount)
{
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, 0.0f, 1.0f));
}

// This method is shared between all EnvParams
void EnvParam::modulate(uint8_t voiceId, float amount)
{
     // mod amount = 1.05^(amount * 100)
    float mod_value = powf(1.05f, abs(amount) * 100.0f);
    if (amount < 0)
    {
        mod_value = -mod_value;
    }
    // mod = original value (ms) + mod amount
    setVoice(voiceId, constrain(value + mod_value, 0.0f, 10616.0f));
}

void EnvDelay::setVoice(uint8_t voiceId, float value_ms)
{
    // time in ms
    voiceArr[voiceId].env[instanceId]->delay(value_ms);
}

void EnvAttack::setVoice(uint8_t voiceId, float value_ms)
{
    // time in ms
    voiceArr[voiceId].env[instanceId]->attack(value_ms);
}

void EnvDecay::setVoice(uint8_t voiceId, float value_ms)
{
    // time in ms
    voiceArr[voiceId].env[instanceId]->decay(value_ms);
}

void EnvSustain::setVoice(uint8_t voiceId, float value)
{
    // 0~1
    voiceArr[voiceId].env[instanceId]->sustain(value);
}

void EnvSustain::modulate(uint8_t voiceId, float amount)
{
    // mod = original value + amount
    setVoice(voiceId, constrain(value + amount, 0.0f, 1.0f));
}

void EnvRelease::setVoice(uint8_t voiceId, float value_ms)
{
    // time in ms
    voiceArr[voiceId].env[instanceId]->release(value_ms);
}
