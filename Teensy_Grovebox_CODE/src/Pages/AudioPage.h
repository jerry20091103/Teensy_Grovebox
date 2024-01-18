#ifndef AUDIOPAGE_H
#define AUDIOPAGE_H

#include "Pages.h"
#include "Audio/AudioIO.h"

#define VOL_MAX 61
#define PAN_MAX 61
#define HP_VOL_MAX 100
#define LINE_GAIN_MAX 15
#define MIC_GAIN_MAX 63

// A page for audio settings
class AudioPage : public Pages
{
private:
    // *user data
    // output tab
    uint8_t OutVol[2] = {51, 51};
    uint8_t hpVol = 50;
    bool usePFL = false;
    // input tab
    uint8_t InVol[2] = {51, 51};
    uint8_t gain[2] = {0, 20};
    bool inputSource = false; // 0-> line; 1-> mic
    // output mixer 
    uint8_t mixerVol[2][4] = {{51, 51, 51 ,51}, {51, 51, 51 ,51}};
    uint8_t mixerPan[2][4] = {{30, 30, 30, 30}, {30, 30, 30, 30}};

    // *class variables
    uint8_t InPeakHold[2][2] = {{0, 0}, {0, 0}};
    uint8_t OutPeakHold[2][2] = {{0, 0}, {0, 0}};
    uint8_t mixerPeakHold[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    MasterTracks currentMasterForMixer = MasterTracks::ANALOG_OUT;
    bool mixerAdjustingPan = false;

    // *lvgl object refs
    lv_obj_t* tabView;
    // output tab
    lv_obj_t *OutArc[2];
    lv_obj_t *OutBar[2][2];
    lv_obj_t *OutPeakLed[2][2];
    lv_obj_t *hpArc;
    lv_obj_t *hpModeLabel;
    lv_obj_t *OutPflBtn;
    // input tab
    lv_obj_t *InArc[2];
    lv_obj_t *InBar[2][2];
    lv_obj_t *InPeakLed[2][2];
    lv_obj_t *gainArc;
    lv_obj_t *lineBtn;
    lv_obj_t *micBtn;
    lv_obj_t *InPflBtn;
    // post-dsp tab
    // output mixer
    lv_obj_t *mixerArc[4];
    lv_obj_t *mixerBar[4][2];
    lv_obj_t *mixerPeakLed[4][2];
    lv_obj_t *mixerWindow;
    lv_obj_t *mixerTitle;

    // lvgl gui callbacks
    static void onTabSwitch(lv_event_t *e);
    static void onPFLBtnPressed(lv_event_t *e);
    static void onInputSwitch(lv_event_t *e);
    static void onArcPressed(lv_event_t *e);
    static void onMixerBtnPressed(lv_event_t *e);
    static void onMixerClose(lv_event_t *e);

    // helper functions
    PROGMEM void createTrackGui(lv_obj_t *&parent, lv_obj_t *&arcRef, lv_obj_t **barArrRef, lv_obj_t **peakArrRef, uint8_t color, const char *name);
    void updateHpVol(uint8_t newVal);
    void updateOutVol(MasterTracks track, uint8_t newVal);
    void setPFL(bool flag);
    void updateInVol(InputTracks track, uint8_t newVal);
    void updateInputGain(uint8_t newVal);
    void updateMixerVol(MixerTracks track, uint8_t newVal);

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
    void load();
    void unload();
};

#endif