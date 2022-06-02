#ifndef ReverbPOPUP_H
#define ReverbPOPUP_H

#include "Pages.h"
#include "Audio/AudioFX.h"

// Popup window for Reverb effect
class ReverbPopup : public Pages
{
private:
    FXFreeverb_Mem *mem;

    void updateRoomSize(uint8_t value);
    void updateDamping(uint8_t value);
    void updateLpf(uint8_t value);
    void updateMix(uint8_t value);

public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onTouch(int ref);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void update();
    void draw();
    void init();
};

#endif