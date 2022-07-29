#ifndef AUDIO_SYNTH_H
#define AUDIO_SYNTH_H

#include "Audio/AudioVoice.h"
#include <list>

#define MAX_VOICE 8

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

    std::list<noteEntry> playingNote;
    std::list<noteEntry> idleNote;

    AudioVoice voiceArr[MAX_VOICE];

    AudioMixer4 *voiceMixer[MAX_VOICE / 4];
    AudioMixer4 *voiceFinalMixer;

    AudioAmplifier *mainVolume[2];

    bool isSustain = false;
    bool useVelocity = true;
    bool usePitchbend = false;
    float curPitchbend = 0;

public:
    PROGMEM AudioSynth_();
    void noteOn(uint8_t note);
    void noteOff(uint8_t note);
    void sustainOn();
    void sustainOff();
    void pitchbend(float semitone);
    void setUseVelocity(bool value);
    void setUsePitchbend(bool value);
    void setSF2Instrument(uint8_t id);
    void setVoiceMode(uint8_t mode);
    void setOscWaveform(uint8_t id, uint8_t wave);
    void setOscOctave(uint8_t id, int8_t value);
    void setOscSemi(uint8_t id, int8_t value);
    void setOscPwm(uint8_t id, uint8_t duty);
    void setOscDetune(uint8_t id, float amount);
    void setOscLevel(uint8_t id, uint8_t amount);
    void setAmpEnvelope(float delay, float attack, float decay, float sustain, float release);
    void setNoiseLevel(float amount);
    void setLadderFreq(float freq);
    void setLadderResonance(float amount);
    void setLadderDrive(float amount);
    void setLadderPassbandGain(float amount);

    // set master output volume in dB
    void setMasterVol(int8_t vol);

    float velocity = 0;
};

extern AudioSynth_ AudioSynth;

#endif