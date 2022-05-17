#ifndef WAVE_TABLE_PAGE_H
#define WAVE_TABLE_PAGE_H

#include "Pages.h"

// A home menu page
class WaveTablePage : public Pages
{
private:
    uint8_t octave = 4;
    float velocity;
public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onTouch(int ref);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void update();
    void draw();
    void init();
};

#endif