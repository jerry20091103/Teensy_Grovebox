#ifndef MIDIPAGE_H
#define MIDIPAGE_H

#include "Pages.h"
#include "GuiObjects/ParamArc.h"
#include "GuiObjects/Spinbox.h"
#include "GuiObjects/Buttons.h"

#define CC_MAX 119
#define CC_MIN 11

class MidiPage : public Pages
{
private:
    // MIDI MMC transport control messages
    const uint8_t playMsg[4] = {0x7f, 0x01, 0x06, 0x02};
    const uint8_t stopMsg[4] = {0x7f, 0x01, 0x06, 0x01};
    const uint8_t forwardMsg[4] = {0x7f, 0x01, 0x06, 0x04};
    const uint8_t rewindMsg[4] = {0x7f, 0x01, 0x06, 0x05};
    const uint8_t recordMsg[4] = {0x7f, 0x01, 0x06, 0x07};

    // GUI object refs
    ParamArc *ccArc[4] = {nullptr};
    Spinbox *octaveSpinbox = nullptr;
    Spinbox *channelSpinbox = nullptr;
    Button *pitchBtn = nullptr;
    Button *modBtn = nullptr;

    // user data
    uint16_t curCC[4] = {11, 12, 13, 14}; // stores the current CC number each encoder is set to
    uint16_t storeCC[109];                // stores all CC values, addressable CC starts from 11 to 119
    bool encConfigure[4] = {false};       // true if an enc is in configure state, CC maping can be changed in this state
    uint16_t octave = 4;
    uint16_t midiChannel = 1;
    bool usePitchbend = true;
    bool useModwheel = true;

    // update stored CC as well as displayed CC
    void updateCC(uint8_t control, uint8_t value);
    // toggle configuire state of an encoder
    void toggleEncConfigure(uint8_t id);
    // Gui object callbacks
    static void onCcArcTurned(void *targetPointer, lv_obj_t *valueTextObj, int16_t value, int8_t encoderIndex);
    static void onTogglePitchbend(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onToggleModwheel(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onOctaveSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);
    static void onChannelSelect(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);

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
    PROGMEM void load();
    PROGMEM void unload();
    void serialize(ofstream& stream) override;
    void deserialize(ifstream& stream) override;
};

#endif