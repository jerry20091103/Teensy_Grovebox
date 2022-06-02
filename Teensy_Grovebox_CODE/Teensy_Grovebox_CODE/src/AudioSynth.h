#ifndef AUDIO_SYNTH_H
#define AUDIO_SYNTH_H

#include "AudioVoice.h"
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
        noteEntry(){}
        noteEntry(uint8_t note, uint8_t voiceInd) : note(note), voiceIndex(voiceInd) {}
        uint8_t note; // the MIDI note number
        uint8_t voiceIndex; // the assigned voice in the voiceArr[] array
    };
    
    std::list<noteEntry> playingNote;
    std::list<noteEntry> idleNote;
    
    AudioVoice voiceArr[MAX_VOICE];

    AudioMixer4 *voiceMixer[MAX_VOICE/4];
    AudioMixer4 *voiceFinalMixer;

    bool isSustain = false;
public:
    AudioSynth_();
    void noteOn(uint8_t note);
    void noteOff(uint8_t note);
    void sustainOn();
    void sustainOff();

    float velocity = 0;

};

extern AudioSynth_ AudioSynth;





#endif