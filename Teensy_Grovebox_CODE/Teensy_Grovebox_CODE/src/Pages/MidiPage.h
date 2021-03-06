#ifndef MIDIPAGE_H
#define MIDIPAGE_H

#include "Pages.h"

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

    // lvgl object refs
    lv_obj_t *ccText[4];
    lv_obj_t *ccArc[4];
    lv_obj_t *octaveText;
    lv_obj_t *channelText;
    lv_obj_t *pitchBtn;
    lv_obj_t *modBtn;

    // user data
    uint8_t curCC[4] = {11, 12, 13, 14}; // stores the current CC number each encoder is set to
    uint8_t storeCC[109];                // stores all CC values, addressable CC starts from 11 to 119
    bool encConfigure[4] = {false};       // true if an enc is in configure state, CC maping can be changed in this state
    uint8_t octave = 4;
    uint8_t midiChannel = 1;
    bool usePitchbend = true;
    bool useModwheel = true;

    // update stored CC as well as displayed CC
    void updateCC(uint8_t control, uint8_t value);
    // toggle configuire state of an encoder
    void toggleEncConfigure(uint8_t id);
    // lvgl gui callbacks
    static void onArcValueChanged(lv_event_t *e);
    static void onTogglePitchbend(lv_event_t *e);
    static void onToggleModwheel(lv_event_t *e);
    static void onOctaveInc(lv_event_t *e);
    static void onOctaveDec(lv_event_t *e);
    static void onChannelInc(lv_event_t *e);
    static void onChannelDec(lv_event_t *e);

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
};

#endif