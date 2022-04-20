#ifndef TEST_H
#define TEST_H

#include "Hardware.h"

extern String debugString;
extern unsigned long lastScreenUpdate;
extern unsigned long lastBarUpdate ;
extern uint8_t bar_test;
extern uint8_t batt_level;

void onBtnPressed(pinid_t pin, bool isHeld);
void onEnc0Turned(int value);
void onEnc1Turned(int value);
void onEnc2Turned(int value);
void onEnc3Turned(int value);

unsigned long testText(int brightness);

#endif