#ifndef WAVE_TABLE_PAGE_H
#define WAVE_TABLE_PAGE_H

#include "Pages.h"
#include "Audio/AudioFX.h"

#define PEAK_AVG_TIME 2

// A home menu page
class WaveTablePage : public Pages
{
private:
    uint8_t octave = 4;
    int8_t volume = 0;

    // gslc_tsElemRef *peakBox;
    float peakAvg = 0;
    uint8_t peakHold = 0;

    void setVolume(int8_t value);
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
    
    FXFreeverb_Mem reverbMem;
};

#endif