#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H

#include <Audio.h>
#include "Audio/AudioObjects.h"

// Synth voices for wave table synth and normal synth.
class AudioVoice
{
private:
public:
    AudioVoice();
    void noteOn(float freq, float amp = 0.9);
    void noteOff();
    void setInstrument(const AudioSynthWavetable::instrument_data &instrument);
    AudioSynthWavetable *waveTable;
    bool isNoteOn = false;
};

#endif