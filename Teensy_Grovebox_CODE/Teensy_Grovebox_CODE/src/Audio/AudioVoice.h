#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H

#include <Audio.h>
#include "Audio/AudioObjects.h"

enum voiceMode
{
    VOICE_MODE_WAVETABLE,
    VOICE_MODE_SYNTH
};

enum waveformType
{
    WAVE_SINE,
    WAVE_TRIANGLE,
    WAVE_SAW,
    WAVE_SQUARE
};

// Synth voices for wave table synth and normal synth.
class AudioVoice
{
private:
    void setOscFreq(uint8_t id, float freq);
public:
    AudioVoice();
    void noteOn(float freq, float amp = 0.9);
    void noteOff();
    void setPitchbend(float semitone);
    void setInstrument(const AudioSynthWavetable::instrument_data &instrument);
    void setVoiceMode(uint8_t mode);
    void setOscWaveform(uint8_t id, uint8_t wave);
    void setOscOctave(uint8_t id, int8_t value);
    void setOscSemi(uint8_t id, int8_t value);
    void setOscPwm(uint8_t id, uint8_t duty);
    void setOscDetune(uint8_t id, float amount);
    void setOscLevel(uint8_t id, float amount);
    void setAmpEnvelope(float delay, float attack, float decay, float sustain, float release);
    void setNoiseLevel(float amount);
    
    AudioMixer4 *voiceSwitch;
    AudioSynthWavetable *waveTable;
    AudioSynthWaveform *waveform[2];
    AudioSynthNoiseWhite *noise;
    AudioEffectEnvelope *ampEnv;
    float frequency;
    uint8_t curVoiceMode;
    bool isNoteOn = false;
    int8_t oscOctave[2] = {0, 0};
    int8_t oscSemi[2] = {0, 0};
    float oscDetune[2] = {0.0f, 0.0f};
};

#endif