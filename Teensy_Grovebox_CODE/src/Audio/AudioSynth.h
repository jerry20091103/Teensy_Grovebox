#ifndef AUDIO_SYNTH_H
#define AUDIO_SYNTH_H

#include <list>
#include "Audio/AudioVoice.h"
#include "Audio/SynthModParam.h"

// converts midi note number to pitch frequency
float noteToFreq(uint8_t note);

// Synth object that manages voice pool, voice mixing, voice parameters, modulations, and effects.
class AudioSynth_
{
private:
    struct noteEntry
    {
        noteEntry() {}
        noteEntry(uint8_t note, uint8_t voiceInd) : note(note), voiceIndex(voiceInd) {}
        uint8_t note;       // the MIDI note number
        uint8_t voiceIndex; // the assigned voice in the voiceArr[] array
    };

    /*
        A list or synth parameters with modulation function.
    */
    class ModParamList
    {
    public:
        ModParamList(AudioVoice *voiceArr);
        OscPitchOffset oscPitchOffset[2];
        OscLevel oscLevel[2];
        OscPwm oscPwm[2];
        NoiseLevel noiseLevel;
        FilterCutoff filterCutoff;
        FilterResonance filterResonance;
        LfoFreq lfoFreq[2];
        LfoLevel lfoLevel[2];
        EnvDelay envDelay[3];
        EnvAttack envAttack[3];
        EnvDecay envDecay[3];
        EnvSustain envSustain[3];
        EnvRelease envRelease[3];
        
        // overload the [] operator, so we can access the parameters by index in the UI.
        SynthModParam& operator[] (uint8_t index)
        {
            switch (index)
            {
            case MOD_TGT_OSC1_FREQ: return oscPitchOffset[0];
            case MOD_TGT_OSC1_LEVEL: return oscLevel[0];
            case MOD_TGT_OSC1_PWM: return oscPwm[0];
            case MOD_TGT_OSC2_FREQ: return oscPitchOffset[1];
            case MOD_TGT_OSC2_LEVEL: return oscLevel[1];
            case MOD_TGT_OSC2_PWM: return oscPwm[1];
            case MOD_TGT_NOISE_LEVEL: return noiseLevel;
            case MOD_TGT_FILTER_CUTOFF: return filterCutoff;
            case MOD_TGT_FILTER_RESONANCE: return filterResonance;
            case MOD_TGT_LFO1_FREQ: return lfoFreq[0];
            case MOD_TGT_LFO1_LEVEL: return lfoLevel[0];
            case MOD_TGT_LFO2_FREQ: return lfoFreq[1];
            case MOD_TGT_LFO2_LEVEL: return lfoLevel[1];
            case MOD_TGT_AMPENV_DELAY: return envDelay[0];
            case MOD_TGT_AMPENV_ATTACK: return envAttack[0];
            case MOD_TGT_AMPENV_DECAY: return envDecay[0];
            case MOD_TGT_AMPENV_SUSTAIN: return envSustain[0];
            case MOD_TGT_AMPENV_RELEASE: return envRelease[0];
            case MOD_TGT_ENV1_DELAY: return envDelay[1];
            case MOD_TGT_ENV1_ATTACK: return envAttack[1];
            case MOD_TGT_ENV1_DECAY: return envDecay[1];
            case MOD_TGT_ENV1_SUSTAIN: return envSustain[1];
            case MOD_TGT_ENV1_RELEASE: return envRelease[1];
            case MOD_TGT_ENV2_DELAY: return envDelay[2];
            case MOD_TGT_ENV2_ATTACK: return envAttack[2];
            case MOD_TGT_ENV2_DECAY: return envDecay[2];
            case MOD_TGT_ENV2_SUSTAIN: return envSustain[2];
            case MOD_TGT_ENV2_RELEASE: return envRelease[2];
            default:
                Serial.println("ERROR: ModParamList::operator[], index out of range.");
                return oscPitchOffset[0];
            }
        }
    }
    modParamList;

    // calculates and sets the pitch offset value using current octave, semi, detune and pitchbend values.
    void calAndSetOscPitchOffset(uint8_t id);

    std::list<noteEntry> playingNote;
    std::list<noteEntry> idleNote;

    AudioVoice voiceArr[MAX_VOICE];

    AudioMixer4 *voiceMixer[MAX_VOICE / 4];
    AudioMixer4 *voiceFinalMixer;

    AudioAmplifier *mainVolume[2];

    bool isSustain = false;
    bool useVelocity = true;

    std::list<ModulationEntry> modList;

public:
    PROGMEM AudioSynth_();
    // * play functions
    void noteOn(uint8_t note);
    void noteOff(uint8_t note);
    void sustainOn();
    void sustainOff();
    void pitchbend(float semitone, float amount);
    void modwheel(float amount);
    // * set parameters
    void setUseVelocity(bool value);
    void setSF2Instrument(uint8_t id);
    void setVoiceMode(uint8_t mode);
    void setOscWaveform(uint8_t id, uint8_t wave);
    void setOscOctave(uint8_t id, int8_t value);
    void setOscSemi(uint8_t id, int8_t value);
    void setOscPwm(uint8_t id, uint8_t duty);
    void setOscDetune(uint8_t id, float amount);
    void setOscLevel(uint8_t id, uint8_t amount);
    void setNoiseLevel(float amount);
    void setLadderFreq(float freq);
    void setLadderResonance(float amount);
    void setLadderDrive(float amount);
    void setLadderPassbandGain(float amount);
    void setLfoWaveform(uint8_t id, uint8_t wave);
    void setLfoFreq(uint8_t id, float freq);
    void setLfoLevel(uint8_t id, float level);
    void setEnvDelay(uint8_t id, float delay);
    void setEnvAttack(uint8_t id, float attack);
    void setEnvDecay(uint8_t id, float decay);
    void setEnvSustain(uint8_t id, float sustain);
    void setEnvRelease(uint8_t id, float release);
    // *modulation
    int8_t addModulation(uint8_t source, uint8_t target);
    void setModulationAmount(uint8_t id, float amount);
    void setModulationSource(uint8_t id, uint8_t source);
    void setModulationTarget(uint8_t id, uint8_t target);
    void resetModulation(uint8_t id);
    void removeModulation(uint8_t id);
    void updateModulation();

    // set master output volume in dB
    void setMasterVol(int8_t vol);

    float velocity = 0.0f;
    float curModWheel = 0.0f;
    float curPitchbend = 0.0f;
    float curPitchbendMult = 1.0f;

    uint8_t curVoiceMode = 0;

    int8_t oscOctave[2] = {0, 0};
    int8_t oscSemi[2] = {0, 0};
    float oscDetune[2] = {0.0f, 0.0f};
};

extern AudioSynth_ AudioSynth;

#endif