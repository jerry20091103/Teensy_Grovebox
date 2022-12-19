#ifndef CONTROLS_H
#define CONTROLS_H

#include "Hardware.h"

#define JOY_THRES 3

// Controls
// Conntect common control callbacks to the callbacks in current page
// Piano key number convertion

// Common button callback function
void BtnPressCallback(pinid_t pin, bool isHeld);
void BtnReleaseCallback(pinid_t pin, bool isHeld);
void Enc0Callback(int value);
void Enc1Callback(int value);
void Enc2Callback(int value);
void Enc3Callback(int value);

// MIDI callbacks
void onControlChange(byte channel, byte control, byte value);

// Joystick polling
void UpdateJoystick();

uint8_t PinToKeyNum(uint8_t pin);

#endif