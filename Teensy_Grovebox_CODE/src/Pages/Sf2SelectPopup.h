#ifndef SF2_SELECT_POPUP_H
#define SF2_SELECT_POPUP_H

#include "Pages.h"

// Popup window for Sf2 sound Selection
class Sf2SelectPopup : public Pages
{
private:
    uint16_t curSelection;
    uint16_t curPage;
public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void update();
    void init();
};

#endif