#ifndef AUDIO_UTILITY_H
#define AUDIO_UTILITY_H

#include "Arduino.h"
#include <Audio.h>

// * Data types

// Represents a single audio block of int16_t samples
struct audio_block_data_t
{
    int16_t data[AUDIO_BLOCK_SAMPLES];
};

// * Utility functions

inline float dBtoGain(float dB) { return pow10f(dB * 0.05); }

inline float gaintodB(float gain) { return 20 * log10f(gain); }

inline float noteToFreq(uint8_t note) { return powf(2, (float)(note - 69) / 12.0f) * 440.0f; }

#endif