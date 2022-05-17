#include "AudioVoice.h"

AudioVoice::AudioVoice()
{
}

void AudioVoice::noteOn(float freq, float amp)
{
    waveTable->playFrequency(freq);
    waveTable->amplitude(amp);
    Serial.println("Entering AudioVoice::noteOn(), freq = " + String(freq) + " veloctiy = " + String(amp));
}

void AudioVoice::noteOff()
{
    waveTable->stop();
}

void AudioVoice::setInstrument(const AudioSynthWavetable::instrument_data *instrument)
{
    waveTable->setInstrument(*instrument);
}