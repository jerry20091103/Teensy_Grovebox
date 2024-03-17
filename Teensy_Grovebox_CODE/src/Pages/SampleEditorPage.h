#ifndef SAMPLEEDITORPAGE_H
#define SAMPLEEDITORPAGE_H

#include "Pages.h"
#include "GuiObjects/Buttons.h"
#include "GuiObjects/VolumeBar.h"
#include "GuiObjects/Slider.h"

class SampleEditorPage : public Pages
{
public:
    Button *recordBtn; // Needs to be public for reocrd cancel callback

private:
    // * lvgl objects
    lv_obj_t *waveformChart = nullptr;
    lv_obj_t *cursorGroup = nullptr;
    lv_obj_t *currentPosCursor = nullptr;
    lv_chart_series_t *serMax = nullptr;
    lv_chart_series_t *serMin = nullptr;
    // * gui objects
    Button *playBtn = nullptr;
    Button *loopBtn = nullptr;
    Button *normalizeBtn = nullptr;
    Button *reverseBtn = nullptr;
    VolumeBar *volBar = nullptr;
    Slider *crossFadeSlider = nullptr;
    // * other variables
    taskid_t cancelRecordTaskId;
    // create a cursor on the waveform display
    lv_obj_t *createCursor(lv_obj_t *parent, lv_color_t color, const char *text, bool reverse = false);
    static void setCursorColor(lv_obj_t *cursor, lv_color_t color);
    // checks cursor bounds and updates cursor position
    void setCursorPos(uint8_t id, float pos);
    // gui object callbacks
    static void onRecordButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onPlayButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onLoopButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onNormailzeButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onReverseButtonPressed(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void onCrossFadeSliderPressed(void *targetPointer, int value);
    // lvgl gui callbacks
    static void onCursorDragged(lv_event_t *event);

    // * user data
    float cursorPos[4] = {0.0f, 0.4f, 0.6f, 1.0f};
    float crossFade = 0.0f;
    bool isLooping = false;

public:
    void onBtnPressed(uint8_t pin);
    void onBtnHold(uint8_t pin);
    void onBtnReleased(uint8_t pin);
    void onEncTurned(uint8_t id, int value);
    void onJoyUpdate(int joy_x, int joy_y);
    void onCCReceive(u_int8_t channel, u_int8_t control, u_int8_t value);
    void configurePage();

    void update();
    PROGMEM void init();
    PROGMEM void load();
    PROGMEM void unload();
    void serialize(ofstream& stream) override;
    void deserialize(ifstream& stream) override;
};

#endif