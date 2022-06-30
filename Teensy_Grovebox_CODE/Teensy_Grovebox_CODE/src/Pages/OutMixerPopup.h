#ifndef OUTMIXERPOPUP_H
#define OUTMIXERPOPUP_H

#include "Pages.h"
#include "Audio/AudioIO.h"

#define TRACK_VOL_MAX 61
#define TRACK_PAN_MAX 60

// Output mixer window to adjust level and pan for each input
// Used on both Analog out and USB out.
class OutMixerPopup : public Pages
{
private:
    
    uint8_t trackVol[2][4] = {{51, 51, 51 ,51}, {51, 51, 51 ,51}};
    uint8_t trackPan[2][4] = {{30, 30, 30, 30}, {30, 30, 30, 30}};
    bool usePFL = false;

    uint8_t peakHold[2][2] = {{0, 0}, {0, 0}};
    // gslc_tsElemRef *peakBox[3][2];
    // gslc_tsElemRef *peakBar[3][2];

    MasterTracks currentMasterTrack = MasterTracks::ANALOG_OUT;
    bool adjustingPan = false;

    void setPFL(bool flag);
    void updateTrackVol(MixerTracks track, uint8_t value);
    void updateTrackPan(MixerTracks track, uint8_t value);
    void changeEncState(bool pan);
    
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