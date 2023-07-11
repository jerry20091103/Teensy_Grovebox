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
    // *user data
    uint8_t octave = 4;
    int8_t volume = 0;
    uint8_t pitchbendRange = 2;
    bool useVelocity = true;
    bool usePitchbend = false;
    bool useModwheel = true;
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
    // env1 and env2
    uint8_t envVal[2][5] = {{0, 0, 0, 100, 0}, {0, 0, 0, 100, 0}};
    // filter
    uint16_t filterVal[4] = {300, 0, 0, 0};
    // lfo
    uint8_t lfoWaveform[2] = {0, 0};
    uint16_t lfoVal[2][2] = {{0, 50}, {0, 50}};
    // sampler
    uint8_t samplerRootKey = 60; // C4
    int8_t samplerTune = 0;
    uint8_t samplerLevel = 90;

    // *class variables
    // gslc_tsElemRef *peakBox;
    float peakAvg = 0;
    uint8_t peakHold = 0;
    bool seletctingRootKey = false;
    const char* setRootKeyBtns[2] = {"Set", ""};

    // *lvgl object refs
    lv_obj_t* menu;
    lv_obj_t* menu_main;
    lv_obj_t* menu_osc[2];
    lv_obj_t* menu_noise;
    lv_obj_t* menu_ampenv;
    lv_obj_t* menu_env[2];
    lv_obj_t* menu_filter;
    lv_obj_t* menu_lfo[2];
    lv_obj_t* menu_mod;
    lv_obj_t* menu_sampler;
    lv_obj_t* volArc;
    lv_obj_t* volBar;
    lv_obj_t* peakLed;
    lv_obj_t* octaveSpinbox;
    lv_obj_t* pitchDropdown;
    lv_obj_t* pitchText;
    lv_obj_t* pitchBtn;
    lv_obj_t* velocityBtn;
    // osc1 and osc 2 share the same objects
    lv_obj_t* oscMenuArea;
    lv_obj_t* oscWaveDropdown;
    lv_obj_t* oscWaveImg;
    lv_obj_t* oscWaveItemImg[2]; // the is on the main menu buttons, so we need 2 for 2 OSCs
    lv_obj_t* oscOctaveSpinbox;
    lv_obj_t* oscSemiSpinbox;
    lv_obj_t* oscArc[3];
    // noise
    lv_obj_t *noiseArc;
    // ampEnv, env1 and env2 share the same objects
    lv_obj_t* envMenuArea;
    lv_obj_t* envGraph;
    lv_point_t envPoints[10];
    lv_obj_t* envArc[5];
    // filter
    lv_obj_t* filterArc[4];
    // lfo
    lv_obj_t* lfoWaveDropdown[2];
    lv_obj_t* lfoWaveImg[2];
    lv_obj_t* lfoWaveItemImg[2];
    lv_obj_t* lfoArc[2][2];
    // modulation
    lv_obj_t* modMenuArea; // this object is used with column flex layout
    lv_obj_t* newModBtn;
    // sampler
    lv_obj_t* waveformChart;
    lv_chart_series_t *serMax;
    lv_chart_series_t *serMin;
    lv_obj_t* rootKeyBtn;
    lv_obj_t* samplerArc[2];
    lv_obj_t* rootKeySelectTitleText;

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
    // envs
    static void onEnvArcPressed(lv_event_t *e);
    // filter
    static void onFilterArcPressed(lv_event_t *e);
    // lfo
    static void onLfoWaveSelect(lv_event_t* e);
    static void onLfoArcPressed(lv_event_t *e);
    // modulation
    static void onNewModBtnPressed(lv_event_t *e);
    static void onDelModBtnPressed(lv_event_t *e);
    static void onModSourceChange(lv_event_t *e);
    static void onModTargetChange(lv_event_t *e);
    static void onModAmountChange(lv_event_t *e);
    // sampler
    static void onSamplerWaveformChartPressed(lv_event_t *e);
    static void onSamplerArcPressed(lv_event_t *e);
    static void onSamplerRootKeyBtnPressed(lv_event_t *e);
    static void onSamplerRootKeySelectSetPressed(lv_event_t *e);

    // *helper functions
    void configureEncoders();
    lv_obj_t* createItemBtn(lv_obj_t* parent, const char* text);
    lv_obj_t* createItemMenuArea(lv_obj_t* menu);
    const lv_img_dsc_t* getOscWaveImg(uint8_t id);
    const lv_img_dsc_t* getLfoWaveImg(uint8_t id);
    lv_obj_t* createModEntry(lv_obj_t* parent, int8_t id);
    lv_obj_t* createNewModBtn(lv_obj_t* parent);
    static String noteNumToNoteName(uint8_t keyNum);

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

private:
    // modulation dropdown option string
    const char* modSourceStr = {"------\n"
    "LFO1\n"
    "LFO2\n"
    "AMPENV\n"
    "ENV1\n"
    "ENV2\n"
    "PitchBend\n"
    "ModWheel\n"
    "Pitch\n"
    "Velocity"};
    const char* modTargetStr = {"------\n"
    "OSC1-Freq\n"
    "OSC1-Level\n"
    "OSC1-PWM\n"
    "OSC2-Freq\n"
    "OSC2-Level\n"
    "OSC2-PWM\n"
    "Noise-Level\n"
    "Filter-Cutoff\n"
    "Filter-Resonance\n"
    "LFO1-Freq\n"
    "LFO1-Level\n"
    "LFO2-Freq\n"
    "LFO2-Level\n"
    "AMPENV-Delay\n"
    "AMPENV-Attack\n"
    "AMPENV-Decay\n"
    "AMPENV-Sustain\n"
    "AMPENV-Release\n"
    "ENV1-Delay\n"
    "ENV1-Attack\n"
    "ENV1-Decay\n"
    "ENV1-Sustain\n"
    "ENV1-Release\n"
    "ENV2-Delay\n"
    "ENV2-Attack\n"
    "ENV2-Decay\n"
    "ENV2-Sustain\n"
    "ENV2-Release\n"
    "Clip-Level"};
};

#endif