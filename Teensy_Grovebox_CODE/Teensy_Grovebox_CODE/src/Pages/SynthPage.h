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
    // osc
    uint8_t oscWaveform[2] = {0, 0};
    int8_t oscOctave[2] = {0, 0};
    int8_t oscSemi[2] = {0, 0};
    uint8_t oscPwm[2] = {50, 50};
    int8_t oscDetune[2] = {0, 0};
    uint8_t oscLevel[2] = {90, 90};


    // *class variables
    // gslc_tsElemRef *peakBox;
    float peakAvg = 0;
    uint8_t peakHold = 0;

    // *lvgl object refs
    lv_obj_t* menu;
    lv_obj_t* menu_main;
    lv_obj_t* menu_osc[2];
    lv_obj_t* volArc;
    lv_obj_t* volText;
    lv_obj_t* volBar;
    lv_obj_t* peakLed;
    lv_obj_t* octaveText;
    lv_obj_t* pitchDropdown;
    lv_obj_t* pitchText;
    // osc
    lv_obj_t* oscWaveImg[2];
    lv_obj_t* oscWaveItemImg[2];
    lv_obj_t* oscOctaveText[2];
    lv_obj_t* oscSemiText[2];
    lv_obj_t* oscArc[2][3];
    lv_obj_t* oscPwmText[2];
    lv_obj_t* oscDetuneText[2];
    lv_obj_t* oscLevelText[2];

    // *lvgl gui callbacks
    static void onVelocityBtnPressed(lv_event_t* e);
    static void onPitchBtnPressed(lv_event_t* e);
    static void onPitchBtnHolded(lv_event_t* e);
    static void onPitchDropdownSelect(lv_event_t *e);
    static void onOctaveSelect(lv_event_t* e);
    static void onVolArcPressed(lv_event_t *e);
    static void onMenuPageChange(lv_event_t *e);
    // osc
    static void onOscWaveSelect(lv_event_t* e);
    static void onOscArcPressed(lv_event_t *e);
    static void onOscOctaveSelect(lv_event_t* e);
    static void onOscSemiSelect(lv_event_t* e);

    // *helper functions
    void configureEncoders();
    lv_obj_t* createItemBtn(lv_obj_t* parent, const char* text);
    lv_obj_t* createItemMenuArea(lv_obj_t* menu);
    const lv_img_dsc_t* getWaveImg(uint8_t id);

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