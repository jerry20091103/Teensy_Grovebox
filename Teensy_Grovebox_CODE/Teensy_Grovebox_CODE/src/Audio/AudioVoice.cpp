#include "AudioVoice.h"

AudioVoice::AudioVoice()
{
}

void AudioVoice::noteOn(float freq, float amp)
{
    frequency = freq;
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        waveform->frequency(freq);
        waveform->amplitude(amp);
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
        waveform->amplitude(0);
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
        waveform->frequency(frequency * powf(2.0f, semitone / 12.0f));
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
void AudioVoice::setSynthWaveform(uint8_t id)
{
    waveform->begin(id);
}