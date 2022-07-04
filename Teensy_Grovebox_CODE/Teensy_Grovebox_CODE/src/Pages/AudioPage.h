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
    // output tab
    lv_obj_t *OutArc[2];
    lv_obj_t *OutVolText[2];
    lv_obj_t *OutBar[2][2];
    lv_obj_t *OutPeakLed[2][2];
    lv_obj_t *hpArc;
    lv_obj_t *hpModeLabel;
    lv_obj_t *hpVolText;
    // input tab
    lv_obj_t *InArc[2];
    lv_obj_t *InVolText[2];
    lv_obj_t *InBar[2][2];
    lv_obj_t *InPeakLed[2][2];
    lv_obj_t *gainArc;
    lv_obj_t *gainText;
    lv_obj_t *lineBtn;
    lv_obj_t *micBtn;
    // post-dsp tab
    // output mixer
    lv_obj_t *mixerArc[4];
    lv_obj_t *mixerVolText[4];
    lv_obj_t *mixerBar[4][2];
    lv_obj_t *mixerPeakLed[4][2];

    // helper functions
    PROGMEM void createTrackGui(lv_obj_t *&parent, lv_obj_t *&arcRef, lv_obj_t *&volTextRef, lv_obj_t **barArrRef, lv_obj_t **peakArrRef, uint8_t color, const char *name);

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