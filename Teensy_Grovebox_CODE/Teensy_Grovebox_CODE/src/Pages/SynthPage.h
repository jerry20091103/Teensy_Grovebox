#ifndef SYNTH_PAGE_H
#define SYNTH_PAGE_H

#include "Pages.h"
#include "Audio/AudioFX.h"

#define PEAK_AVG_TIME 2
#define VOL_OFFSET 15

// Substractive synth page
class SynthPage : public Pages
{
private:
    // *user data
    uint8_t octave = 4;
    int8_t volume = 0;
    uint8_t pitchbendRange = 2;
    bool useVelocity = true;
    bool usePitchbend = false;


    // *class variables
    // gslc_tsElemRef *peakBox;
    float peakAvg = 0;
    uint8_t peakHold = 0;

    // *lvgl object refs
    lv_obj_t* volArc;
    lv_obj_t* volText;
    lv_obj_t* volBar;
    lv_obj_t* peakLed;
    lv_obj_t* octaveText;
    lv_obj_t* pitchDropdown;
    lv_obj_t* pitchText;

    // lvgl gui callbacks
    static void onVelocityBtnPressed(lv_event_t* e);
    static void onPitchBtnPressed(lv_event_t* e);
    static void onPitchBtnHolded(lv_event_t* e);
    static void onPitchDropdownSelect(lv_event_t *e);
    static void onOctaveSelect(lv_event_t* e);
    static void onVolArcPressed(lv_event_t *e);
    // helper functions
    void setVolume(int8_t value);

public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void update();
    void init();
    
    // *user data
    FXFreeverb_Mem reverbMem;
};

#endif