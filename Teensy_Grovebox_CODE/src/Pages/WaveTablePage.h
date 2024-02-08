#ifndef WAVE_TABLE_PAGE_H
#define WAVE_TABLE_PAGE_H

#include "Pages.h"
#include "Audio/AudioFX.h"
#include "GuiObjects/ParamArc.h"
#include "GuiObjects/Spinbox.h"
#include "GuiObjects/Buttons.h"
#include "GuiObjects/VolumeBar.h"

// sf2 Wave table synth page
class WaveTablePage : public Pages
{
private:
    // *user data
    uint8_t octave = 4;
    int8_t volume = 0;
    uint8_t pitchbendRange = 2;
    uint8_t curInstrument = 0;
    bool useVelocity = true;
    bool usePitchbend = false;

    // *lvgl object refs
    lv_obj_t* selectGroup = nullptr;
    lv_obj_t* sf2SelectDropdown = nullptr;
    lv_obj_t* pitchDropdown = nullptr;

    // *GUI object refs
    ParamArc* volArc = nullptr;
    Spinbox* octaveSpinbox = nullptr;
    Button* velocityBtn = nullptr;
    Button* pitchBtn = nullptr;
    VolumeBar* volBar = nullptr;

    // Gui object callbacks
    static void onVolArcTurned(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
    static void onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);
    static void onVelocityBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onPitchBtnPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onPitchBtnHolded(void *targetPointer, lv_obj_t *labelObj);
    // lvgl gui callbacks
    static void onPitchDropdownSelect(lv_event_t *e);
    static void onSF2DropdownSelect(lv_event_t *e);
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
    void setUserData();

    void update();
    PROGMEM void init();
    PROGMEM void load();
    PROGMEM void unload();
    
    // *user data
    FXFreeverb_Mem reverbMem;
};

#endif