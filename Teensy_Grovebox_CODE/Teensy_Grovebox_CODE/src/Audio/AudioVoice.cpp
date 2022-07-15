#include "AudioVoice.h"
#include "AudioUtility.h"

AudioVoice::AudioVoice()
{
}

void AudioVoice::setOscFreq(uint8_t id, float freq)
{
    if (oscOctave[id] || oscSemi[id] || oscDetune[id])
        freq *= (powf(2, oscOctave[id] + (((float)oscSemi[id] + oscDetune[id]) / 12.0f)));

    waveform[id]->frequency(freq);
}

void AudioVoice::noteOn(float freq, float amp)
{
    frequency = freq;
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        setOscFreq(0, freq);
        setOscFreq(1, freq);
        waveform[0]->amplitude(amp);
        waveform[1]->amplitude(amp);
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->playFrequency(freq);
        waveTable->amplitude(amp);
        break;
    }
}

void AudioVoice::noteOff()
{
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        waveform[0]->amplitude(0);
        waveform[1]->amplitude(0);
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->stop();
        break;
    }
}

void AudioVoice::setInstrument(const AudioSynthWavetable::instrument_data &instrument)
{
    waveTable->setInstrument(instrument);
}

// set the amount of pitch bend in semitones
void AudioVoice::setPitchbend(float semitone)
{
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        setOscFreq(0, frequency * powf(2.0f, semitone / 12.0f));
        setOscFreq(1, frequency * powf(2.0f, semitone / 12.0f));
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->setFrequency(frequency * powf(2.0f, semitone / 12.0f));
        break;
    }
}

// use the audio mixer to select voice mode (soucre of voice)
void AudioVoice::setVoiceMode(uint8_t mode)
{
    curVoiceMode = mode;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (i == mode)
        {
            voiceSwitch->gain(1.0f, i);
        }
        else
        {
            voiceSwitch->gain(0.0f, i);
        }
    }
}

// set the output waveform of the synth voice
void AudioVoice::setOscWaveform(uint8_t id, uint8_t wave)
{
    switch (wave)
    {
    case WAVE_SINE:
        waveform[id]->begin(WAVEFORM_SINE);
        break;
    case WAVE_TRIANGLE:
        waveform[id]->begin(WAVEFORM_TRIANGLE);
        break;
    case WAVE_SAW:
        waveform[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        break;
    case WAVE_SQUARE:
        waveform[id]->begin(WAVEFORM_BANDLIMIT_PULSE);
        break;
    }
}

void AudioVoice::setOscOctave(uint8_t id, int8_t value)
{
    oscOctave[id] = value;
    setOscFreq(id, frequency);
}

void AudioVoice::setOscSemi(uint8_t id, int8_t value)
{
    oscSemi[id] = value;
    setOscFreq(id, frequency);
}

void AudioVoice::setOscPwm(uint8_t id, uint8_t duty)
{
    waveform[id]->pulseWidth(duty * 0.01f);
}

void AudioVoice::setOscDetune(uint8_t id, float amount)
{
    oscDetune[id] = amount;
    setOscFreq(id, frequency);
}

void AudioVoice::setOscLevel(uint8_t id, float amount)
{
    
    waveform[id]->amplitude(amount);
}