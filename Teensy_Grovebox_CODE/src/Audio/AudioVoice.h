#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H

#include <Audio.h>
#include "Audio/AudioObjects.h"
#include <list>

#define MAX_VOICE 8
#define MAX_MODULATION_COUNT 127

enum voiceMode
{
    VOICE_MODE_WAVETABLE,
    VOICE_MODE_SYNTH,
    VOICE_MODE_SAMPLE_EDITER
};

enum oscWaveformType
{
    WAVE_OSC_SINE,
    WAVE_OSC_TRIANGLE,
    WAVE_OSC_SAW,
    WAVE_OSC_SQUARE
};

enum lfoWaveformType
{
    WAVE_LFO_SINE,
    WAVE_LFO_TRIANGLE,
    WAVE_LFO_SAW,
    WAVE_LFO_SAW_REV,
    WAVE_LFO_SQUARE,
    WAVE_LFO_SAMPLE_HOLD
};

enum modSource
{
    MOD_SRC_NONE,
    MOD_SRC_LFO1,
    MOD_SRC_LFO2,
    MOD_SRC_AMPENV,
    MOD_SRC_ENV1,
    MOD_SRC_ENV2,
    MOD_SRC_PITCHBEND,
    MOD_SRC_MODWHEEL,
    MOD_SRC_PITCH,
    MOD_SRC_VELOCITY,
    MOD_SRC_MAX
};

enum modTarget
{
    MOD_TGT_NONE,
    MOD_TGT_OSC1_FREQ,
    MOD_TGT_OSC1_LEVEL,
    MOD_TGT_OSC1_PWM,
    MOD_TGT_OSC2_FREQ,
    MOD_TGT_OSC2_LEVEL,
    MOD_TGT_OSC2_PWM,
    MOD_TGT_NOISE_LEVEL,
    MOD_TGT_FILTER_CUTOFF,
    MOD_TGT_FILTER_RESONANCE,
    MOD_TGT_LFO1_FREQ,
    MOD_TGT_LFO1_LEVEL,
    MOD_TGT_LFO2_FREQ,
    MOD_TGT_LFO2_LEVEL,
    MOD_TGT_AMPENV_DELAY,
    MOD_TGT_AMPENV_ATTACK,
    MOD_TGT_AMPENV_DECAY,
    MOD_TGT_AMPENV_SUSTAIN,
    MOD_TGT_AMPENV_RELEASE,
    MOD_TGT_ENV1_DELAY,
    MOD_TGT_ENV1_ATTACK,
    MOD_TGT_ENV1_DECAY,
    MOD_TGT_ENV1_SUSTAIN,
    MOD_TGT_ENV1_RELEASE,
    MOD_TGT_ENV2_DELAY,
    MOD_TGT_ENV2_ATTACK,
    MOD_TGT_ENV2_DECAY,
    MOD_TGT_ENV2_SUSTAIN,
    MOD_TGT_ENV2_RELEASE,
    MOD_TGT_MAX
};

struct ModulationEntry
{
    ModulationEntry();
    ModulationEntry(modSource source, modTarget target, float amount) : source(source), target(target), amount(amount) {}
    modSource source;
    modTarget target;
    float amount;
    // overload the == operator, we don't care about the "amount" when comparing two ModulationEntries
    bool operator==(const ModulationEntry& other) const
    {
        return (source == other.source && target == other.target);
    }
};

// Synth voices for wave table synth and normal synth.
class AudioVoice
{
public:
    void setOscFreq(uint8_t id, float freq);
    AudioVoice();
    // *play functions
    void noteOn(uint8_t note, float amp = 0.9);
    void noteOff();
    void setPitchbend(float semitone);
    // *set parameters
    inline void setInstrument(const AudioSynthWavetable::instrument_data &instrument) { waveTable->setInstrument(instrument); }
    void setVoiceMode(uint8_t mode);
    void setOscWaveform(uint8_t id, uint8_t wave);
    inline void setLadderDrive(float amount) { ladderFilter->inputDrive(amount); }
    inline void setLadderPassbandGain(float amount) { ladderFilter->passbandGain(amount); }
    void setLfoWaveform(uint8_t id, uint8_t wave);
    void setSampleBaseNote(uint8_t note);
    void setSampleNoteOffset(float offset);

    AudioMixer4 *voiceSwitch;
    AudioSynthWavetable *waveTable;
    AudioSynthWaveform *waveform[2];
    AudioSynthNoiseWhite *noise;
    AudioFilterLadder *ladderFilter;
    AudioSynthWaveform *lfo[2];
    AudioEffectEnvelope *env[3]; // env[0] is the amp envelope
    AudioRecordSample *lfoSample[2];
    AudioRecordSample *envSample[2];
    AudioRecordSample *ampEnvSample;
    AudioPlayClip *playClip;

    float frequency;
    float curAmp = 0.0f;
    float curPitchBendMult = 1.0f;
    float curSampleNoteOffset = 0.0f;
    uint8_t curNote = 60;
    uint8_t curVoiceMode = VOICE_MODE_WAVETABLE;
    uint8_t curSampleBaseNote = 60;
    bool isNoteOn = false;
};

#endif