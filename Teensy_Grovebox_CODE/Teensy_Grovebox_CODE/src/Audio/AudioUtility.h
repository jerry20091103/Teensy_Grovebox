#ifndef AUDIO_UTILITY_H
#define AUDIO_UTILITY_H

#include "Arduino.h"

inline float dBtoGain(float dB) { return pow10f(dB * 0.05); }

inline float gaintodB(float gain) { return 20 * log10f(gain); }

#endif