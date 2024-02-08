#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "Pages.h"

// A home menu page
class HomePage : public Pages
{
private:
    // lvgl object refs
    lv_obj_t *btnMatrix = nullptr;

    // lvgl gui callbacks
    static void onBtnPressed(lv_event_t *e);

    // button map
    const char* btnMap[12] = {
        "Synth", "Wavetable", "\n",
        "MIDI", "Drum", "\n",
        "Record", "Keybaord", "\n",
        "FX", "Settings", ""
    };
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