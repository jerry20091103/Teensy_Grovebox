#include "AudioVoice.h"

AudioVoice::AudioVoice()
{
}

void AudioVoice::noteOn(float freq, float amp)
{
    waveTable->playFrequency(freq);
    waveTable->amplitude(amp);
    frequency = freq;
    Serial.println("Entering AudioVoice::noteOn(), freq = " + String(freq) + " veloctiy = " + String(amp));
}

void AudioVoice::noteOff()
{
    waveTable->stop();
}

void AudioVoice::setInstrument(const AudioSynthWavetable::instrument_data &instrument)
{
    waveTable->setInstrument(instrument);
}

// set the amount of pitch bend in semitones
void AudioVoice::setPitchbend(float semitone)
{
    waveTable->setFrequency(frequency * powf(2.0f, semitone / 12.0f));
}