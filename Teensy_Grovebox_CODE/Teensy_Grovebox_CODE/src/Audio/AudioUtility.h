#ifndef AUDIO_UTILITY_H
#define AUDIO_UTILITY_H

#include "Arduino.h"

inline float dBtoGain(float dB) { return pow10f(dB * 0.05); }

inline float gaintodB(float gain) { return 20 * log10f(gain); }

inline float noteToFreq(uint8_t note) { return powf(2, (float)(note - 69) / 12.0f) * 440.0f; }

#endif