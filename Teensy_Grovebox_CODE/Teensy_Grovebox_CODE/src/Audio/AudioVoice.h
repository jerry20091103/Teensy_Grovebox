#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H

#include <Audio.h>
#include "Audio/AudioObjects.h"

enum voiceMode
{
    VOICE_MODE_WAVETABLE,
    VOICE_MODE_SYNTH
};

// Synth voices for wave table synth and normal synth.
class AudioVoice
{
private:
public:
    AudioVoice();
    void noteOn(float freq, float amp = 0.9);
    void noteOff();
    void setPitchbend(float semitone);
    void setInstrument(const AudioSynthWavetable::instrument_data &instrument);
    void setVoiceMode(uint8_t mode);
    void setSynthWaveform(uint8_t id);
    AudioMixer4 *voiceSwitch;
    AudioSynthWavetable *waveTable;
    AudioSynthWaveform *waveform;
    float frequency;
    uint8_t curVoiceMode;
    bool isNoteOn = false;
};

#endif