#ifndef SYNTH_PAGE_H
#define SYNTH_PAGE_H

#include "Pages.h"
#include "Audio/AudioFX.h"
#include "GuiObjects/ParamArc.h"
#include "GuiObjects/Buttons.h"
#include "GuiObjects/Spinbox.h"
#include "GuiObjects/EnvelopeGraph.h"
#include "GuiObjects/VolumeBar.h"

#define PEAK_AVG_TIME 2
#define ENV_VAL_MAX 190
#define ENV_VAL_INCREMENT 1.05f

// Substractive synth page
class SynthPage : public PageWithSubPage
{
private:
    // forward declaration of subpages
    class MainPage;
    class OscPage;
    class SamplerPage;
    class NoisePage;
    class FilterPage;
    class ModPage;
    class EnvPage;
    class LfoPage;

    // subpages
    MainPage* mainPage = nullptr;
    OscPage* oscPage[2] = {nullptr};
    SamplerPage* samplerPage = nullptr;
    NoisePage* noisePage = nullptr;
    FilterPage* filterPage = nullptr;
    ModPage* modPage = nullptr;
    EnvPage* envPage[3] = {nullptr};
    LfoPage* lfoPage[2] = {nullptr};

    // *lvgl object refs
    lv_obj_t* subpageGroup;

    // TODO: a shared function for subpages to create the top navigation bar?

    // *helper functions
    lv_obj_t* createTopBar(lv_obj_t* parent, const char* title);
    static String noteNumToNoteName(uint8_t keyNum);

public:
    void onBtnPressedDefault(uint8_t pin) override;
    void onBtnHoldDefault(uint8_t pin) override;
    void onBtnReleasedDefault(uint8_t pin) override;
    void onEncTurnedDefault(uint8_t id, int value) override;
    void onJoyUpdateDefault(int joy_x, int joy_y) override;
    void onCCReceiveDefault(u_int8_t channel, u_int8_t control, u_int8_t value) override;
    void configurePage() override;

    void updateDefault() override;
    PROGMEM void init() override;
    void loadAll() override;
    
    // *user data
    FXFreeverb_Mem reverbMem;

private:
    

    class MainPage : public SubPage
    {
        friend class SynthPage;
    private:
        // user data
        uint8_t octave = 4;
        int8_t volume = 0;
        uint8_t pitchbendRange = 2;
        bool useVelocity = false;
        bool usePitchbend = false;
        bool useModwheel = true; // TODO: Add modwheel enable button?
        // gui objects
        ParamArc* volArc = nullptr;
        Spinbox* octaveSpinbox = nullptr;
        Button* velocityBtn = nullptr;
        Button* pitchBtn = nullptr;
        VolumeBar* volBar = nullptr;
        // lvgl object refs
        lv_obj_t* pitchDropdown;
        lv_obj_t* oscWaveItemImg[2] = {nullptr}; // the is on the main menu buttons, so we need 2 for 2 OSCs
        lv_obj_t* lfoWaveItemImg[2] = {nullptr};
    public:
        MainPage(PageWithSubPage* parent) : SubPage(parent) {}
        void load() override;
        void unload() override;
        void update() override;
    private:
        // gui callback functions
        static void onVolArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onVelocityBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
        static void onPitchBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
        static void onPitchBtnHolded(void *targetPointer, lv_obj_t *labelObj);
        static void onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);
        // lvgl callback functions
        static void onPitchDropdownSelect(lv_event_t *e);
        // helper functions
        lv_obj_t* createItemBtn(lv_obj_t* parent, const char* text);
        lv_obj_t* createItemMenuColumn(lv_obj_t* parent);
    };

    class OscPage : public SubPage
    {
        friend class SynthPage;
    private:
        // instance id
        uint8_t id;
        // user data
        uint8_t oscWaveform = 0;
        int8_t oscOctave = 0;
        int8_t oscSemi = 0;
        uint8_t oscPwm = 50;
        int8_t oscDetune = 0;
        uint8_t oscLevel = 90;
        // gui objects
        Spinbox* oscOctaveSpinbox = nullptr;
        Spinbox* oscSemiSpinbox = nullptr;
        ParamArc* oscArc[3] = {nullptr};
        // lvgl object refs
        lv_obj_t* oscWaveDropdown = nullptr;
        lv_obj_t* oscWaveImg = nullptr;
    public:
        OscPage(PageWithSubPage* parent, uint8_t id) : SubPage(parent), id(id) {}
        void load() override;
        void unload() override;
    private:
        // gui callback functions
        static void onOscOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);
        static void onOscSemiSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);
        static void onOscArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        // lvgl callback functions
        static void onOscWaveSelect(lv_event_t* e);
        // helper functions
        const lv_img_dsc_t* getOscWaveImg();
    };

    class SamplerPage : public SubPage
    {
        friend class SynthPage;
    private:
        // user data
        uint8_t samplerRootKey = 60; // C4
        int8_t samplerTune = 0;
        uint8_t samplerLevel = 90;
        // gui objects
        ParamArc* samplerArc[2] = {nullptr};
        Button* rootKeyBtn = nullptr;
        // lvgl object refs
        lv_obj_t* waveformChart = nullptr;
        lv_chart_series_t *serMax = nullptr;
        lv_chart_series_t *serMin = nullptr;
        lv_obj_t* rootKeySelectTitleText = nullptr;
        // other variables
        bool seletctingRootKey = false;
        const char* setRootKeyBtns[2] = {"Set", ""};
    public:
        SamplerPage(PageWithSubPage* parent) : SubPage(parent) {}
        void load() override;
        void unload() override;
        void onBtnPressed(uint8_t pin) override;
    private:
        // gui callback functions
        static void onSamplerArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onSamplerRootKeyBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
        // lvgl callback functions
        static void onSamplerWaveformChartPressed(lv_event_t *e);
        static void onSamplerRootKeySelectSetPressed(lv_event_t *e);
    };

    class NoisePage : public SubPage
    {
        friend class SynthPage;
    private:
        // user data
        uint8_t noiseLevel = 0;
        // gui objects
        ParamArc* noiseArc = nullptr;
        // lvgl object refs
    public:
        NoisePage(PageWithSubPage* parent) : SubPage(parent) {}
        void load() override;
        void unload() override;
    private:
        // gui callback functions
        static void onNoiseArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
    };

    class FilterPage : public SubPage
    {
        friend class SynthPage;
    private:
        // user data
        uint16_t filterVal[4] = {300, 0, 0, 0};
        // gui objects
        ParamArc* filterArc[4] = {nullptr};
    public:
        FilterPage(PageWithSubPage* parent) : SubPage(parent) {}
        void load() override;
        void unload() override;
    private:
        // gui callback functions
        static void onFilterArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
    };

    class ModPage : public SubPage
    {
        friend class SynthPage;
    private:
        // user data
        // TODO: save modulation list here
        // gui objects
        // lvgl object refs
        lv_obj_t* modMenuArea = nullptr; // this object is used with column flex layout
        lv_obj_t* newModBtn = nullptr;
    public:
        ModPage(PageWithSubPage* parent) : SubPage(parent) {}
        void load() override;
        void unload() override;
    private:
        // gui callback functions
        // lvgl callback functions
        static void onNewModBtnPressed(lv_event_t *e);
        static void onDelModBtnPressed(lv_event_t *e);
        static void onModSourceChange(lv_event_t *e);
        static void onModTargetChange(lv_event_t *e);
        static void onModAmountChange(lv_event_t *e);
        // helper functions
        lv_obj_t* createModEntry(lv_obj_t* parent, int8_t id);
        lv_obj_t* createNewModBtn(lv_obj_t* parent);
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

    class EnvPage : public SubPage
    {
        friend class SynthPage;
    private:
        // instance id
        uint8_t id;
        // user data
        uint8_t envVal[5] = {0, 0, 0, 100, 0};
        // gui objects
        EnvelopeGraph* envGraph = nullptr;
        ParamArc* envArc[5] = {nullptr};
    public:
        EnvPage(PageWithSubPage* parent, uint8_t id) : SubPage(parent), id(id) {}
        void load() override;
        void unload() override;
    private:
        // gui callback functions
        static void onEnvArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
    };

    class LfoPage : public SubPage
    {
        friend class SynthPage;
    private:
        // instance id
        uint8_t id;
        // user data
        uint8_t lfoWaveform = 0;
        uint16_t lfoVal[2] = {0, 50};
        // gui objects
        ParamArc* lfoArc[2] = {nullptr};
        // lvgl object refs
        lv_obj_t* lfoWaveDropdown = nullptr;
        lv_obj_t* lfoWaveImg = nullptr;
    public:
        LfoPage(PageWithSubPage* parent, uint8_t id) : SubPage(parent), id(id) {}
        void load() override;
        void unload() override;
    private:
        // gui callback functions
        static void onLfoArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        // lvgl callback functions
        static void onLfoWaveSelect(lv_event_t* e);
        // helper functions
        const lv_img_dsc_t* getLfoWaveImg();
    };
};

#endif