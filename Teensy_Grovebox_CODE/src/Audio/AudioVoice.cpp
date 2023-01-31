#include "AudioVoice.h"
#include "AudioUtility.h"
#include "AudioSynth.h"

AudioVoice::AudioVoice()
{
}

void AudioVoice::setOscFreq(uint8_t id, float freq)
{
    waveform[id]->frequency(freq);
}

void AudioVoice::noteOn(uint8_t note, float amp)
{
    frequency = noteToFreq(note);
    curNote = note;
    curAmp = amp;
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        setOscFreq(0, frequency);
        setOscFreq(1, frequency);
        waveform[0]->amplitude(amp);
        waveform[1]->amplitude(amp);
        env[0]->noteOn();
        env[1]->noteOn();
        env[2]->noteOn();
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->playFrequency(frequency);
        waveTable->amplitude(amp);
        break;
    }
}

void AudioVoice::noteOff()
{
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        env[0]->noteOff();
        env[1]->noteOff();
        env[2]->noteOff();
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->stop();
        break;
    }
}

// set the amount of pitch bend in semitones
void AudioVoice::setPitchbend(float pitchMult)
{
    curPitchBendMult = pitchMult;
    switch (curVoiceMode)
    {
    case VOICE_MODE_SYNTH:
        // do nothing for now
        break;

    case VOICE_MODE_WAVETABLE:
        waveTable->setFrequency(frequency * pitchMult);
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
    case WAVE_OSC_SINE:
        waveform[id]->begin(WAVEFORM_SINE);
        break;
    case WAVE_OSC_TRIANGLE:
        waveform[id]->begin(WAVEFORM_TRIANGLE);
        break;
    case WAVE_OSC_SAW:
        waveform[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        break;
    case WAVE_OSC_SQUARE:
        waveform[id]->begin(WAVEFORM_BANDLIMIT_PULSE);
        break;
    }
}

void AudioVoice::setLfoWaveform(uint8_t id, uint8_t wave)
{
    switch (wave)
    {
    case WAVE_LFO_SINE:
        lfo[id]->begin(WAVEFORM_SINE);
        break;
    case WAVE_LFO_TRIANGLE:
        lfo[id]->begin(WAVEFORM_TRIANGLE);
        break;
    case WAVE_LFO_SAW:
        lfo[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        break;
    case WAVE_LFO_SAW_REV:
        lfo[id]->begin(WAVEFORM_BANDLIMIT_SAWTOOTH_REVERSE);
        break;
    case WAVE_LFO_SQUARE:
        lfo[id]->begin(WAVEFORM_BANDLIMIT_PULSE);
        break;
    case WAVE_LFO_SAMPLE_HOLD:
        lfo[id]->begin(WAVEFORM_SAMPLE_HOLD);
        break;
    }
}