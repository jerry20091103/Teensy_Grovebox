#ifndef SYNTH_PAGE_H
#define SYNTH_PAGE_H

#include "Pages.h"
#include "Audio/AudioFX.h"

#define PEAK_AVG_TIME 2
#define VOL_OFFSET 15
#define ENV_VAL_MAX 190
#define ENV_VAL_INCREMENT 1.05f

// Substractive synth page
class SynthPage : public Pages
{
private:
    // todo: add permenant memory
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
    // noise
    uint8_t noiseLevel = 0;
    // amp env
    uint8_t ampEnvVal[5] = {0, 0, 0, 100, 0};
    // filter
    uint16_t filterVal[4] = {300, 0, 0, 0};

    // *class variables
    // gslc_tsElemRef *peakBox;
    float peakAvg = 0;
    uint8_t peakHold = 0;

    // *lvgl object refs
    lv_obj_t* menu;
    lv_obj_t* menu_main;
    lv_obj_t* menu_osc[2];
    lv_obj_t* menu_noise;
    lv_obj_t* menu_ampenv;
    lv_obj_t* menu_filter;
    lv_obj_t* volArc;
    lv_obj_t* volText;
    lv_obj_t* volBar;
    lv_obj_t* peakLed;
    lv_obj_t* octaveText;
    lv_obj_t* pitchDropdown;
    lv_obj_t* pitchText;
    lv_obj_t* pitchBtn;
    lv_obj_t* velocityBtn;
    // osc
    lv_obj_t *oscWaveDropdown[2];
    lv_obj_t* oscWaveImg[2];
    lv_obj_t* oscWaveItemImg[2];
    lv_obj_t* oscOctaveText[2];
    lv_obj_t* oscSemiText[2];
    lv_obj_t* oscArc[2][3];
    lv_obj_t* oscPwmText[2];
    lv_obj_t* oscDetuneText[2];
    lv_obj_t* oscLevelText[2];
    // noise
    lv_obj_t *noiseArc;
    lv_obj_t *noiseLevelText;
    // amp env
    lv_obj_t* ampEnvGraph;
    lv_point_t ampEnvPoints[10];
    lv_obj_t* ampEnvText[5];
    lv_obj_t* ampEnvArc[5];
    // filter
    lv_obj_t* filterArc[4];
    lv_obj_t* filterText[4];

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
    // noise
    static void onNoiseArcPressed(lv_event_t *e);
    // amp env
    static void onAmpEnvArcPressed(lv_event_t *e);
    // filter
    static void onFilterArcPressed(lv_event_t *e);

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
    void setUserData();

    void update();
    PROGMEM void init();
    
    // *user data
    FXFreeverb_Mem reverbMem;
};

#endif