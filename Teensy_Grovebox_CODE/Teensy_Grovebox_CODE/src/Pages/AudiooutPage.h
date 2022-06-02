#ifndef AUDIOOUTPAGE_H
#define AUDIOOUTPAGE_H

#include "Pages.h"
#include "Audio/AudioIO.h"

#define MASTER_VOL_MAX 63
#define RMS_AVG_TIME 5

// A page for audio output adjustments and audio quick settings.
// Also links to output mixer popup for further adjustments.
class AudiooutPage : public Pages
{
private:
    uint8_t analogOutVol = 43;
    uint8_t usbOutVol = 43;
    uint8_t hpVol = 15;
    bool usePFL = false;

    float rmsAvg[2] = {0, 0};
    uint8_t peakHold[2][2] = {{0, 0}, {0, 0}};

    gslc_tsElemRef *peakBox[2][2];
    gslc_tsElemRef *peakBar[2][2];
    gslc_tsElemRef *rmsBar[2];

    void updateHpVol(uint8_t newVal);
    void updateOutVolume(MasterTracks track, uint8_t newVal);
    void setPFL(bool flag);
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