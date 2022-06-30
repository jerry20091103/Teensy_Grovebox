#ifndef AUDIOINPAGE_H
#define AUDIOINPAGE_H

#include "Pages.h"
#include "Audio/AudioIO.h"

#define INPUT_VOL_MAX 61
#define LINE_GAIN_MAX 15
#define MIC_GAIN_MAX 63

// A page for audio input adjustments
class AudioinPage : public Pages
{
private:
    bool inputSource = false; // 0-> line; 1-> mic
    bool usePFL = false;
    uint8_t inputGain[2] = {0, 20};
    uint8_t inputVol[2] = {51, 51};

    uint8_t peakHold[2][2] = {{0, 0}, {0, 0}};
    // gslc_tsElemRef *peakBox[2][2];
    // gslc_tsElemRef *peakBar[2][2];

    void setInputGain(uint8_t value);
    void setPFL(bool flag);
    void updateInputVol(InputTracks track, uint8_t value);
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