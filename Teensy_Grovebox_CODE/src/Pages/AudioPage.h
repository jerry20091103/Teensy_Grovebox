#ifndef AUDIOPAGE_H
#define AUDIOPAGE_H

#include "Pages.h"
#include "Audio/AudioIO.h"
#include "GuiObjects/Buttons.h"
#include "GuiObjects/ParamArc.h"
#include "GuiObjects/VolumeBar.h"

#define VOL_MAX 61
#define PAN_MIN -50
#define PAN_MAX 50
#define HP_VOL_MAX 100
#define LINE_GAIN_MAX 15
#define MIC_GAIN_MAX 63

// A page for audio settings
class AudioPage : public PageWithSubPage
{
private:
    // forward declaration of subpages
    class MainPage;
    class MixerPage;

    // subpage instances
    MainPage *mainPage = nullptr;
    MixerPage *mixerPage[2] = {nullptr};

    // *lvgl object refs
    lv_obj_t* subpageGroup = nullptr;

    // helper functions
    static void createTrackGui(lv_obj_t *parent, ParamArc *&arcRef, VolumeBar **barArrRef, uint8_t color, const char *name);
    static void createMixerTrackGui(lv_obj_t *parent, ParamArcMini *&volArcRef, ParamArcMini *&panArcRef, VolumeBar **barArrRef, uint8_t color, const char *name);
    lv_obj_t *createTopBar(lv_obj_t *parent, const char *title);

public:
    void onBtnPressedDefault(uint8_t pin);
    void onBtnHoldDefault(uint8_t pin);
    void onBtnReleasedDefault(uint8_t pin);
    void onEncTurnedDefault(uint8_t id, int value);
    void onJoyUpdateDefault(int joy_x, int joy_y);
    void onCCReceiveDefault(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void updateDefault();
    PROGMEM void init();
    void loadAll();
    void serialize(ofstream& stream) override;
    void deserialize(ifstream& stream) override;

private:
    class MainPage : public SubPage
    {
        friend class AudioPage;
    private:
        // *user data
        uint16_t curTab = 0;
        // output tab
        uint16_t OutVol[2] = {51, 51};
        uint16_t hpVol = 50;
        bool usePFL = false;
        // input tab
        uint16_t InVol[2] = {51, 51};
        uint16_t gain[2] = {0, 20};
        bool inputSource = false; // 0-> line; 1-> mic
        // *gui objects
        // output tab
        ParamArc *OutArc[2] = {nullptr};
        VolumeBar *OutBar[2][2] = {{nullptr}};
        Button *OutPflBtn = nullptr;
        ParamArc *hpArc = nullptr;
        // input tab
        ParamArc *InArc[2] = {nullptr};
        VolumeBar *InBar[2][2] = {{nullptr}};
        ParamArc *gainArc = nullptr;
        Button *lineBtn = nullptr;
        Button *micBtn = nullptr;
        Button *InPflBtn = nullptr;
        // post dsp tab
        // *lvgl object refs
        lv_obj_t* tabView = nullptr;
    public:
        MainPage(PageWithSubPage *parent) : SubPage(parent) {}
        void load() override;
        void unload() override;
        void update() override;
        void serialize(ofstream& stream) override;
        void deserialize(ifstream& stream) override;
    private:
        // gui callback functions
        static void onOutputArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onHpArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onMainPFLBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
        static void onInputArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onGainArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onLineSourceSelect(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
        static void onMicSourceSelect(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
        // lvgl callback functions
        static void onTabSwitch(lv_event_t *e);
        // helper functions
    };

    class MixerPage : public SubPage
    {
        friend class AudioPage;
    private:
        // instance id
        uint8_t id;
        // user data
        uint16_t mixerVol[4] = {51, 51, 51 ,51};
        uint16_t mixerPan[4] = {0, 0, 0, 0};
        // gui objects
        VolumeBar *mixerBar[4][2] = {{nullptr}};
        ParamArcMini *mixerPanArc[4] = {nullptr};
        ParamArcMini *mixerVolArc[4] = {nullptr};
        // lvgl object refs
    public:
        MixerPage(PageWithSubPage *parent, uint8_t id) : SubPage(parent), id(id) {}
        void load() override;
        void unload() override;
        void update() override;
        void serialize(ofstream& stream) override;
        void deserialize(ifstream& stream) override;
    private:
        // gui callback functions
        static void onMixerVolArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        static void onMixerPanArcPressed(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
        // lvgl callback functions
        // helper functions
    };
};

#endif