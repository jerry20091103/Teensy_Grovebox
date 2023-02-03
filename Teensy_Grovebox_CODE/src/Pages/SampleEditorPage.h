#ifndef SAMPLEEDITORPAGE_H
#define SAMPLEEDITORPAGE_H

#include "Pages.h"


class SampleEditorPage : public Pages
{
private:
    lv_obj_t *waveformChart;
    lv_obj_t *cursorGroup;
    lv_obj_t *recordBtn;
    lv_obj_t *playBtn;
    lv_obj_t *stopBtn;
    lv_obj_t *loopBtn;
    lv_chart_series_t * serMax;
    lv_chart_series_t * serMin;
    int16_t waveformPointsMax[1000];
    int16_t waveformPointsMin[1000];
    void loadWaveformChart(int16_t *data, int length);
    lv_obj_t* createCursor(lv_obj_t *parent, lv_color_t color, const char *text, bool reverse = false);
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