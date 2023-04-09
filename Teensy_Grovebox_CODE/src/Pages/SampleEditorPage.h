#ifndef SAMPLEEDITORPAGE_H
#define SAMPLEEDITORPAGE_H

#include "Pages.h"

class SampleEditorPage : public Pages
{
public:
    lv_obj_t *recordBtn; // Needs to be public for reocrd cancel callback

private:
    lv_obj_t *waveformChart;
    lv_obj_t *cursorGroup;
    lv_obj_t *currentPosCursor;
    lv_obj_t *playBtn;
    lv_obj_t *loopBtn;
    lv_obj_t *normalizeBtn;
    lv_obj_t *reverseBtn;
    lv_obj_t *volBar;
    lv_obj_t *peakLed;
    lv_chart_series_t *serMax;
    lv_chart_series_t *serMin;
    taskid_t cancelRecordTaskId;
    uint8_t peakHold = 0;
    float peakAvg = 0;
    // create a cursor on the waveform display
    lv_obj_t *createCursor(lv_obj_t *parent, lv_color_t color, const char *text, bool reverse = false);
    static void setCursorColor(lv_obj_t *cursor, lv_color_t color);
    // checks cursor bounds and updates cursor position
    void setCursorPos(uint8_t id, float pos);
    // lvgl gui callbacks
    static void onRecordButtonPressed(lv_event_t *event);
    static void onPlayButtonPressed(lv_event_t *event);
    static void onLoopButtonPressed(lv_event_t *event);
    static void onNormailzeButtonPressed(lv_event_t *event);
    static void onReverseButtonPressed(lv_event_t *event);
    static void onCursorDragged(lv_event_t *event);
    static void onCrossFadeSliderPressed(lv_event_t *event);

    // * user data
    GuiUserData<float> cursorPos[4] = {
        GuiUserData<float>(0.0f, 0, [](float value, int8_t id)
                           { AudioSynth.setClipStartPoint(value); }),
        GuiUserData<float>(0.4f, 1, [](float value, int8_t id)
                           { AudioSynth.setClipLoopStartPoint(value); }),
        GuiUserData<float>(0.6f, 2, [](float value, int8_t id)
                           { AudioSynth.setClipLoopEndPoint(value); }),
        GuiUserData<float>(1.0f, 3, [](float value, int8_t id)
                           { AudioSynth.setClipEndPoint(value); })};

    GuiUserData<float> crossFade = GuiUserData<float>(0.0f, 0, [](float value, int8_t id)
                                                      { AudioSynth.setClipLoopCrossfade(value); });

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