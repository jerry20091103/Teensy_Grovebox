#ifndef CONTROLS_H
#define CONTROLS_H

// Controls
// Provides an abstraction from hardware to software controls with callbacks

#include "Hardware.h"

class Controls
{
private:
    /* data */
public:
    Controls(/* args */);
    ~Controls();
};

Controls::Controls(/* args */)
{
}


void BtnCallback(pinid_t pin, bool isHeld);

void OnBtnPressed(uint8_t pin);
void OnBtnHold(uint8_t pin);
void OnBtnReleased(uint8_t pin);

#endif