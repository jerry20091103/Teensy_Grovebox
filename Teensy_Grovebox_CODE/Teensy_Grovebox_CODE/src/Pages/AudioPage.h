#ifndef AUDIOPAGE_H
#define AUDIOPAGE_H

#include "Pages.h"

// A home menu page
class AudioPage : public Pages
{
private:
    // user data
    bool usePFL = false;

    // lvgl object refs
    lv_obj_t *OutArc[2];
    lv_obj_t *OutVolText[2];
    lv_obj_t *OutBar[2][2];
    lv_obj_t *OutPeakLed[2][2];
    lv_obj_t *hpArc;
    lv_obj_t *hpModeLabel;
    lv_obj_t *hpVolText;

public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void update();
    PROGMEM void init();
};

#endif