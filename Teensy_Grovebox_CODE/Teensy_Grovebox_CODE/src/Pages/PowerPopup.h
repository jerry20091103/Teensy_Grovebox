#ifndef POWERPOPUP_H
#define POWERPOPUP_H

#include "Pages.h"

// Popup window for power off confirmation
class PowerPopup : public Pages
{
private:

public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onTouch(int ref);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configureEncoders();

    void update();
    void draw();
    void init();
};

#endif